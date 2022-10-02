#include "ModelClass.h"

//ModelClass 초기화

ModelClass::ModelClass()
{
	//클래스 생성하면서 버퍼 포인터 초기화
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{

}

ModelClass::~ModelClass()
{

}

bool ModelClass::Initialize(ID3D11Device* device)
{
	bool result;

	//버퍼 초기화
	//전부 Private 내부 함수로 돌아간다.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	//버퍼 해제(정리)하는 내부함수
	ShutdownBuffers();

	return;
}

//GraphicsClass::Render 에서 호출할 ModelClass Render 함수..
//RenderBuffers 함수를 호출하여 정점 버퍼와 인덱스 버퍼를 그래픽 파이프라인에 넣어 컬러 셰이더가 그릴 수 있도록 해줌
void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// 정점 버퍼와 인덱스 버퍼를 그래픽스 파이프라인에 넣어 화면에 그릴 준비를 함
	RenderBuffers(deviceContext);

	return;
}

//해당 모델의 인덱스 개수를 알려주는데, 컬러 셰이더에서 모델을 그리기 위해서 이 정보가 필요하다..
int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

//InitializeBuffers 함수는 정점 버퍼와 인덱스 버퍼를 생성하는 작업을 제어함.
//데이터 파일로부터 모델의 정보를 읽어 와서 버퍼를 만드는 일을 한다..
//지금은 삼각형 하나를 만들것이기 때문에 정점 버퍼와 인덱스 버퍼에 이 점을 세팅하는 일만 함
bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// 정점 배열의 길이 설정 (삼각형이므로 3개)
	m_vertexCount = 4;
	// 인덱스 배열의 길이 설정 (삼각형이므로 3개)
	m_indexCount = 6;

	// 정점 배열을 생성 (vertexCount 만큼)
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// 인덱스 배열 생성
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// 정점/인덱스 배열에 삼각형의 각 점과 그 순서를 채워넣음...
	// 중요한것은 D3DClass 에서 설정했듯이 시계 방향으로 폴리곤을 그려야 앞면으로 인식되어 그려지고
	// 반대로 그려버리면 뒷면이 되므로 Backface Culling 에 의해서 보이지 않게 된다.

	//과제
	//모든 폴리곤은 다 삼각형으로 이루어져있기 때문에
	//사각형을 그리기 위해서는 4개 점을 한번에 주는 것으로는 안되고,
	//삼각형 두개를 같은 위치에 붙여야 사각형으로 보인다.
	//다만 vertex 6개로 삼각형 두개->사각형 만들어줘도 되지만
	//있는 vertex 를 활용해서 만들어 줄 수도 있음 (점을 하나만 추가하고 인덱스를 중복되게 활용하면 된다!)
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); //왼쪽 아래
	vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA 색상

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f); //왼쪽 위
	vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA 색상

	vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f); //오른쪽 위
	vertices[2].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA 색상

	vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f); //오른쪽 아래
	vertices[3].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA 색상

	//인덱스 배열에 순서값을 넣음
	//4개 정점만 이용하기 위해서는 인덱싱을 이렇게 해 줘야 한다
	indices[0] = 0;	//왼쪽아래
	indices[1] = 1;	//왼쪽위
	indices[2] = 2; //오른쪽위
	indices[3] = 3;	//오른쪽아래
	indices[4] = 0;	//다시 왼쪽 아래 (시계방향이어야 하므로)
	indices[5] = 2; //이번엔 오른쪽 위

	//만약 반대로 그렸다면 2, 1, 0 순으로 할당해줬을것임

	//이제 정점, 인덱스 배열 다 채웠으므로 각 버퍼를 만들어 줘야 함
	//D3DClass 에서 진행했던 버퍼 만들기랑 동일하다.
	//Description 작성하고 포인터 연결하고 Create 하여 실제 버퍼에 연결하는 순서

	//정점 버퍼 description 작성
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//버퍼의 크기는 당연 VertexType 크기에 vertex 개수만큼 곱해준 양이 될 것이다.
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	//보통 Flags는 다 종류를 의미한다. 무엇인지. 할지 안할지. 이 버퍼의 타입은 vertexBuffer 으로 사용할 것이므로 정해준다.
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//CPU 사용하지 않음 (GPU연산)
	vertexBufferDesc.CPUAccessFlags = 0;
	//기타설정 없음
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//정점 데이터를 가리키는 보조 리소스 구조체를 작성
	//자세한건 뭔지 모르겠다.
	//이건 아마 vertex 리소스에 대한 메모리를 지정하는거일거고..
	vertexData.pSysMem = vertices;
	//아래 두개는 뭔지 모르겠다..
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//정점 버퍼를 생성
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//인덱스 버퍼도 똑같이 해준다
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	//일정 단위(stride)을 가지고 바이트를 구성할 것인가? -> 0은 일단 아니라는 의미니깐..
	//자세히는 모르겠지만 이런 의미일 것이다
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//다쓴거 해제
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

//만들어진 버퍼 해제
void ModelClass::ShutdownBuffers()
{
	//각 버퍼 할당 해제
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


//우선, 여기의 렌더버퍼는 정점 버퍼와 인덱스 버퍼로 화면 내용을 그리기 위해 필요하다.
//정확하게는 정점 버퍼와 인덱스 버퍼를 GPU의 어셈블리 버퍼로써 활성화시키고
//GPU가 이 활성화된 버퍼들을 가짐으로써 셰이더를 이용하여 이 버퍼에 내용을 그릴 수 있게 되는것.
//여기서는 받은 정점 데이터를 삼각형이나 선분, 부채꼴 등 어떤 모양으로 그릴지 정의할 수 있다.
void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// 정점 버퍼의 단위와 오프셋을 설정
	//Vertex 크기가 단위이므로 데이터를 읽을 때 이만큼씩 떼어서 읽어야 맞겠지?
	stride = sizeof(VertexType);
	//일단 오프셋(데이터 밀림)은 없다.
	offset = 0;

	//input assembler 에 정점 버퍼를 활성화하여 그려질 수 있도록 함
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//이번엔 인덱스 버퍼
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//정점 버퍼로 그릴 기본 도형 -> 여기서는 일단 삼각형 (원래 모든 오브젝트는 삼각형으로 이루어짐)
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}
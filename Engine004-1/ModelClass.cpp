#include "ModelClass.h"

//ModelClass �ʱ�ȭ

ModelClass::ModelClass()
{
	//Ŭ���� �����ϸ鼭 ���� ������ �ʱ�ȭ
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

	//���� �ʱ�ȭ
	//���� Private ���� �Լ��� ���ư���.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::Shutdown()
{
	//���� ����(����)�ϴ� �����Լ�
	ShutdownBuffers();

	return;
}

//GraphicsClass::Render ���� ȣ���� ModelClass Render �Լ�..
//RenderBuffers �Լ��� ȣ���Ͽ� ���� ���ۿ� �ε��� ���۸� �׷��� ���������ο� �־� �÷� ���̴��� �׸� �� �ֵ��� ����
void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// ���� ���ۿ� �ε��� ���۸� �׷��Ƚ� ���������ο� �־� ȭ�鿡 �׸� �غ� ��
	RenderBuffers(deviceContext);

	return;
}

//�ش� ���� �ε��� ������ �˷��ִµ�, �÷� ���̴����� ���� �׸��� ���ؼ� �� ������ �ʿ��ϴ�..
int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

//InitializeBuffers �Լ��� ���� ���ۿ� �ε��� ���۸� �����ϴ� �۾��� ������.
//������ ���Ϸκ��� ���� ������ �о� �ͼ� ���۸� ����� ���� �Ѵ�..
//������ �ﰢ�� �ϳ��� ������̱� ������ ���� ���ۿ� �ε��� ���ۿ� �� ���� �����ϴ� �ϸ� ��
bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// ���� �迭�� ���� ���� (�ﰢ���̹Ƿ� 3��)
	m_vertexCount = 4;
	// �ε��� �迭�� ���� ���� (�ﰢ���̹Ƿ� 3��)
	m_indexCount = 6;

	// ���� �迭�� ���� (vertexCount ��ŭ)
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// �ε��� �迭 ����
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// ����/�ε��� �迭�� �ﰢ���� �� ���� �� ������ ä������...
	// �߿��Ѱ��� D3DClass ���� �����ߵ��� �ð� �������� �������� �׷��� �ո����� �νĵǾ� �׷�����
	// �ݴ�� �׷������� �޸��� �ǹǷ� Backface Culling �� ���ؼ� ������ �ʰ� �ȴ�.

	//����
	//��� �������� �� �ﰢ������ �̷�����ֱ� ������
	//�簢���� �׸��� ���ؼ��� 4�� ���� �ѹ��� �ִ� �����δ� �ȵǰ�,
	//�ﰢ�� �ΰ��� ���� ��ġ�� �ٿ��� �簢������ ���δ�.
	//�ٸ� vertex 6���� �ﰢ�� �ΰ�->�簢�� ������൵ ������
	//�ִ� vertex �� Ȱ���ؼ� ����� �� ���� ���� (���� �ϳ��� �߰��ϰ� �ε����� �ߺ��ǰ� Ȱ���ϸ� �ȴ�!)
	vertices[0].position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); //���� �Ʒ�
	vertices[0].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA ����

	vertices[1].position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f); //���� ��
	vertices[1].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA ����

	vertices[2].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f); //������ ��
	vertices[2].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA ����

	vertices[3].position = D3DXVECTOR3(1.0f, -1.0f, 0.0f); //������ �Ʒ�
	vertices[3].color = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f); //RGBA ����

	//�ε��� �迭�� �������� ����
	//4�� ������ �̿��ϱ� ���ؼ��� �ε����� �̷��� �� ��� �Ѵ�
	indices[0] = 0;	//���ʾƷ�
	indices[1] = 1;	//������
	indices[2] = 2; //��������
	indices[3] = 3;	//�����ʾƷ�
	indices[4] = 0;	//�ٽ� ���� �Ʒ� (�ð�����̾�� �ϹǷ�)
	indices[5] = 2; //�̹��� ������ ��

	//���� �ݴ�� �׷ȴٸ� 2, 1, 0 ������ �Ҵ�����������

	//���� ����, �ε��� �迭 �� ä�����Ƿ� �� ���۸� ����� ��� ��
	//D3DClass ���� �����ߴ� ���� ������ �����ϴ�.
	//Description �ۼ��ϰ� ������ �����ϰ� Create �Ͽ� ���� ���ۿ� �����ϴ� ����

	//���� ���� description �ۼ�
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//������ ũ��� �翬 VertexType ũ�⿡ vertex ������ŭ ������ ���� �� ���̴�.
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	//���� Flags�� �� ������ �ǹ��Ѵ�. ��������. ���� ������. �� ������ Ÿ���� vertexBuffer ���� ����� ���̹Ƿ� �����ش�.
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//CPU ������� ���� (GPU����)
	vertexBufferDesc.CPUAccessFlags = 0;
	//��Ÿ���� ����
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	//���� �����͸� ����Ű�� ���� ���ҽ� ����ü�� �ۼ�
	//�ڼ��Ѱ� ���� �𸣰ڴ�.
	//�̰� �Ƹ� vertex ���ҽ��� ���� �޸𸮸� �����ϴ°��ϰŰ�..
	vertexData.pSysMem = vertices;
	//�Ʒ� �ΰ��� ���� �𸣰ڴ�..
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//���� ���۸� ����
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//�ε��� ���۵� �Ȱ��� ���ش�
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	//���� ����(stride)�� ������ ����Ʈ�� ������ ���ΰ�? -> 0�� �ϴ� �ƴ϶�� �ǹ̴ϱ�..
	//�ڼ����� �𸣰����� �̷� �ǹ��� ���̴�
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//�پ��� ����
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

//������� ���� ����
void ModelClass::ShutdownBuffers()
{
	//�� ���� �Ҵ� ����
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


//�켱, ������ �������۴� ���� ���ۿ� �ε��� ���۷� ȭ�� ������ �׸��� ���� �ʿ��ϴ�.
//��Ȯ�ϰԴ� ���� ���ۿ� �ε��� ���۸� GPU�� ����� ���۷ν� Ȱ��ȭ��Ű��
//GPU�� �� Ȱ��ȭ�� ���۵��� �������ν� ���̴��� �̿��Ͽ� �� ���ۿ� ������ �׸� �� �ְ� �Ǵ°�.
//���⼭�� ���� ���� �����͸� �ﰢ���̳� ����, ��ä�� �� � ������� �׸��� ������ �� �ִ�.
void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// ���� ������ ������ �������� ����
	//Vertex ũ�Ⱑ �����̹Ƿ� �����͸� ���� �� �̸�ŭ�� ��� �о�� �°���?
	stride = sizeof(VertexType);
	//�ϴ� ������(������ �и�)�� ����.
	offset = 0;

	//input assembler �� ���� ���۸� Ȱ��ȭ�Ͽ� �׷��� �� �ֵ��� ��
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//�̹��� �ε��� ����
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//���� ���۷� �׸� �⺻ ���� -> ���⼭�� �ϴ� �ﰢ�� (���� ��� ������Ʈ�� �ﰢ������ �̷����)
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}
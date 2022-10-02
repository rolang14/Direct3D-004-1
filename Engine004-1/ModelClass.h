#pragma once

#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>

//ModelClass 는 3D 모델들의 복합한 기하학들을 캡슐화하는 클래스이다.
//지금은 녹색 삼각형을 만들기 위한 데이터를 차근차근 만들어 볼 것이다.
//삼각형이 그려지기 위해서는 VS,PS 에 더해 이들이 사용할 인덱스 버퍼, 정점 버퍼 역시 필요하므로
class ModelClass
{
private:
	//정점 버퍼에 사용될 정점의 구조체 (VertexType)
	//ColorShaderClass에서 사용할 것과 그 구조가 당연히 같아야 한다.
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	//여기까지 생성, 소멸

	//여기부터는 구현 함수들
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);


private:
	//각각 정점 버퍼와 인덱스 버퍼를 만들어준다. (포인터로 되어있는걸 보아 또...뭔가 메소드가 할당해줄것이다)
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif
#pragma once

#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>

//ModelClass �� 3D �𵨵��� ������ �����е��� ĸ��ȭ�ϴ� Ŭ�����̴�.
//������ ��� �ﰢ���� ����� ���� �����͸� �������� ����� �� ���̴�.
//�ﰢ���� �׷����� ���ؼ��� VS,PS �� ���� �̵��� ����� �ε��� ����, ���� ���� ���� �ʿ��ϹǷ�
class ModelClass
{
private:
	//���� ���ۿ� ���� ������ ����ü (VertexType)
	//ColorShaderClass���� ����� �Ͱ� �� ������ �翬�� ���ƾ� �Ѵ�.
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR4 color;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	//������� ����, �Ҹ�

	//������ʹ� ���� �Լ���
	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	int GetIndexCount();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);


private:
	//���� ���� ���ۿ� �ε��� ���۸� ������ش�. (�����ͷ� �Ǿ��ִ°� ���� ��...���� �޼ҵ尡 �Ҵ����ٰ��̴�)
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_vertexCount, m_indexCount;
};

#endif
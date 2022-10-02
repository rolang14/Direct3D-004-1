#pragma once

//ColorShaderClass -> GPU �� �����ϴ� 3D ���� �׸��� ���� ����ϴ� HLSL ���̴��� ȣ���ϱ� ���� Ŭ����

#ifndef _COLORSHADERCLASS_H_
#define _COLORSHADERCLASS_H_

#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>
#include <fstream>

using namespace std;

class ColorShaderClass
{
private:
	//���⼭ �ٽ� �������ִ� ������, ���� ���̴��� ���� cBuffer Ÿ���� �����ؾ��ϹǷ�
	//�ݵ�� Color.vs ���� ������ cBuffer �� ������ ������ ����ü�� ������ �ش�.
	struct MatrixBufferType
	{
		//3�� ��� ����ü ����
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();
	//���̴��� �ʱ�ȭ�� �������� ������.
	//Render �� ���̴��� ���Ǵ� �������� �����ϰ� ���̴��� �̿��� �غ�� ���� �������� �׷� ��
	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11Buffer* m_matrixBuffer;
};

#endif // !_COLORSHADERCLASS_H_
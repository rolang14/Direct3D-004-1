#pragma once

#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

//GraphicsClass ���� ��� �׷��� ��ü�� ���� ���������� ȣ���� ����Ѵ�.!!

//���� D3D ����� ���� D3D ����� �߰�����.
#include "D3DClass.h"

//Engine004 �߰�-------------------------
//������ ���̴��� �߰��س������� �̸� �����ϱ� ���� ���⼭ ȣ���ؾ� �Ѵ�.
//---------------------------------------
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"



//Ǯ��ũ�� ���
const bool FULL_SCREEN = true;
//V-��ũ ���
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();
	//m_�� �տ� ���̴� ������ ������ ��� �������� �˷��ֱ� ����..
	//m_D3D�� D3D�� ��� ��������.
	D3DClass* m_D3D;

	//Engine004 �߰�-------------------------
	//�������� HLSL ���̴� Ŭ���� �߰�
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
	//---------------------------------------
};

#endif

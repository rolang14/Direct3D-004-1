#pragma once

#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

//GraphicsClass 에서 모든 그래픽 객체에 대한 파이프라인 호출을 담당한다.!!

//이제 D3D 사용을 위해 D3D 헤더를 추가해줌.
#include "D3DClass.h"

//Engine004 추가-------------------------
//이제는 셰이더를 추가해놓았으니 이를 적용하기 위해 여기서 호출해야 한다.
//---------------------------------------
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"



//풀스크린 모드
const bool FULL_SCREEN = true;
//V-싱크 모드
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
	//m_을 앞에 붙이는 이유는 누구의 멤버 변수인지 알려주기 위해..
	//m_D3D는 D3D의 멤버 변수구나.
	D3DClass* m_D3D;

	//Engine004 추가-------------------------
	//만들어놓은 HLSL 셰이더 클래스 추가
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
	//---------------------------------------
};

#endif

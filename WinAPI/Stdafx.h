#pragma once
#pragma comment(lib,"gdiplus")

#include <SDKDDKVer.h>	

//===================================
//! Windows 헤더 파일
//===================================
#define WIN32_LEAN_AND_MEAN          
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

//! 라이브러리
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")//win 멀티 미디어 (그래픽카드를 불러올때도 사용)
#pragma comment (lib, "msimg32.lib")//알파블렌드를 사용하기위한 라이브러리 추가

//===================================
//! C 런타임 헤더 파일
//===================================
//stdlib c언어 표준 라이브러리 함수 헤더 
#include <stdlib.h>
#include <time.h>
#include <tchar.h>
//윈도우 내장 재생 라이브러리
#include <mmsystem.h>

//미디어 컨트롤 인터페이스 api
#include <mciapi.h>


//===================================
//! GDI+ connection
//===================================
#include <Ole2.h>//객체 연결 삽입
#include <gdiplus.h>
using namespace Gdiplus;



//===================================
//! C++ 런타임 헤더
//===================================
#include <iostream>
#include <random>
//bitset: 비트연산을 좀더 쉽게 관리해주는 함수를 지원한다.->STL
//-reset(),set(),flip(),all(),any()
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <typeinfo>
#include <algorithm> 

//void 포인터를 변수처럼 던지는 라이브러리
#include <functional> 

using namespace std;

//===================================
//# 내가 만든 헤더파일을 이곳에 추가 #
//===================================
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "TimeManager.h"
#include "Utils.h"
#include "CRectObserverManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"

using namespace MY_UTIL;
//===================================
//# custom #
//===================================

//===================================
//# SingleTon #
//===================================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER	FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define RECTOBSERVERMANAGER CRectObserverManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()


//===================================
//# 매크로 # (윈도우 초기화)
//===================================

#define WINNAME			(LPSTR)(TEXT("WindowAPI"))

//#define FULLSCREEN

#ifdef FULLSCREEN

//#ifdef FULLSCREEN
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics() : 인자로 전달되는 시스템 설정정보 반환
//ㄴ SM_CXSCREEN : 현재 화면 해상도 X축반환
//ㄴ SM_CYSCREEN : 현재 화면 해상도 Y축반환
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTART_X		350
#define WINSTART_Y		0
#define WINSIZE_X		1000
#define WINSIZE_Y		1000
//#define WINSIZE_Y		700
//WS SYSMENU >> 오른쪽 상단 컨트롤 박스 
//WINSTYLE WS_CAPTION ? 
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#endif 

//===================================
//# 매크로 # (기능 및 효율)
//===================================
#define CENTER_X	WINSIZE_X/2
#define CENTER_Y	WINSIZE_Y/2

//===================================
//# 매크로 함수 # (클래스에서 동적 할당된 부분 해제)
//===================================

#define SAFE_DELETE(p)			{if(p){delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[](p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p){(p)->release(); (p) = nullptr;} }


//각도표기 -> 라디안 표기 변환
#define PI	3.141592653f
#define DEGREE_RADIAN(_deg)			(M_PI * (_deg)/180.0f)
//===================================
//# 전역변수 #
//===================================
//헤더 cpp 에서 변수를 공유해서 쓰기 위함

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;	// 마우스 사용시 xy
//extern mycustom::Image _CImage;  //깡통인데

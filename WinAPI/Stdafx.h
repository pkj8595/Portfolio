#pragma once
#pragma comment(lib,"gdiplus")

#include <SDKDDKVer.h>	

//===================================
//! Windows ��� ����
//===================================
#define WIN32_LEAN_AND_MEAN          
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>

//! ���̺귯��
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")//win ��Ƽ �̵�� (�׷���ī�带 �ҷ��ö��� ���)
#pragma comment (lib, "msimg32.lib")//���ĺ��带 ����ϱ����� ���̺귯�� �߰�

//===================================
//! C ��Ÿ�� ��� ����
//===================================
//stdlib c��� ǥ�� ���̺귯�� �Լ� ��� 
#include <stdlib.h>
#include <time.h>
#include <tchar.h>
//������ ���� ��� ���̺귯��
#include <mmsystem.h>

//�̵�� ��Ʈ�� �������̽� api
#include <mciapi.h>


//===================================
//! GDI+ connection
//===================================
#include <Ole2.h>//��ü ���� ����
#include <gdiplus.h>
using namespace Gdiplus;



//===================================
//! C++ ��Ÿ�� ���
//===================================
#include <iostream>
#include <random>
//bitset: ��Ʈ������ ���� ���� �������ִ� �Լ��� �����Ѵ�.->STL
//-reset(),set(),flip(),all(),any()
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <typeinfo>
#include <algorithm> 

//void �����͸� ����ó�� ������ ���̺귯��
#include <functional> 

using namespace std;

//===================================
//# ���� ���� ��������� �̰��� �߰� #
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
//# ��ũ�� # (������ �ʱ�ȭ)
//===================================

#define WINNAME			(LPSTR)(TEXT("WindowAPI"))

//#define FULLSCREEN

#ifdef FULLSCREEN

//#ifdef FULLSCREEN
#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics() : ���ڷ� ���޵Ǵ� �ý��� �������� ��ȯ
//�� SM_CXSCREEN : ���� ȭ�� �ػ� X���ȯ
//�� SM_CYSCREEN : ���� ȭ�� �ػ� Y���ȯ
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE

#else

#define WINSTART_X		350
#define WINSTART_Y		0
#define WINSIZE_X		1000
#define WINSIZE_Y		1000
//#define WINSIZE_Y		700
//WS SYSMENU >> ������ ��� ��Ʈ�� �ڽ� 
//WINSTYLE WS_CAPTION ? 
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#endif 

//===================================
//# ��ũ�� # (��� �� ȿ��)
//===================================
#define CENTER_X	WINSIZE_X/2
#define CENTER_Y	WINSIZE_Y/2

//===================================
//# ��ũ�� �Լ� # (Ŭ�������� ���� �Ҵ�� �κ� ����)
//===================================

#define SAFE_DELETE(p)			{if(p){delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p){delete[](p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p){(p)->release(); (p) = nullptr;} }


//����ǥ�� -> ���� ǥ�� ��ȯ
#define PI	3.141592653f
#define DEGREE_RADIAN(_deg)			(M_PI * (_deg)/180.0f)
//===================================
//# �������� #
//===================================
//��� cpp ���� ������ �����ؼ� ���� ����

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;	// ���콺 ���� xy
//extern mycustom::Image _CImage;  //�����ε�

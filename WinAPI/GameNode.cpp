#include "Stdafx.h"
#include "GameNode.h"



HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		//로케일 설정(#include "locale.h")
		//LC_ALL : 로케일 카테고리. os에 있는 정보를 끌고옴
		setlocale(LC_ALL, "Korean");
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		RND->init();
		IMAGEMANAGER->init();
		TEMPSOUNDMANAGER->init();
		TIMEMANAGER->init();
		TEXTDATAMANAGER->init();
		RECTOBSERVERMANAGER->init();
		SCENEMANAGER->init();
		CAMERAMANAGER->init();
	}

	//CAMERAMANAGER->startMappingMode(getHDC());
	//CAMERAMANAGER->startMappingMode(_hdc);


	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		KEYMANAGER->releaseSingleton();

		RND->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		FONTMANAGER->releaseSingleton();

		TEMPSOUNDMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();

		RECTOBSERVERMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

	}


	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	//InvalidateRect(_hWnd, NULL, FALSE);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		//this->update();
		break;
	case WM_CREATE:
		break;

	case WM_PAINT:	
		hdc = BeginPaint(hWnd, &ps);
		//this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		DPtoLP(getHDC(), &_ptMouse, 1);

		break;
	case WM_LBUTTONDOWN:	

		break;
	case WM_RBUTTONDOWN:

		break;
	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE:		
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_COMMAND:
		switch (wParam)
		{
			case 0x0001: 
			{
				RECT cameraRc = RectMake(0, 0, 0, 0);
				GetClientRect(_hWnd, &cameraRc);
				SetWindowExtEx(getHDC(), 960, 540, NULL);
				SetViewportExtEx(getHDC(), cameraRc.right, cameraRc.bottom, NULL);
				break;
			}
			case 0x0002: 
			{
				RECT cameraRc = RectMake(0, 0, 0, 0);
				GetClientRect(_hWnd, &cameraRc);
				SetWindowExtEx(getHDC(), cameraRc.right, cameraRc.bottom, NULL);
				SetViewportExtEx(getHDC(), cameraRc.right, cameraRc.bottom, NULL);
				break;
			}
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

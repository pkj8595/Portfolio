#include "Stdafx.h"
#include "MainGame.h"

//=======================
// # 전역변수 #
//=======================
HINSTANCE _hInstance;
//윈도우 핸들
HWND _hWnd;
POINT _ptMouse = { 0,0 };
MainGame* _mg;
LPRECT _cameraRc;

//================
//#함수 전방 선언#
//================
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);

//! window main 함수 
int APIENTRY WinMain( HINSTANCE hInstance,
						HINSTANCE hPrevInstance,
						LPSTR    lpszCmdParam,
						int       nCmdShow)
{
	_mg = new MainGame();

	_hInstance = hInstance;

	//GDI+
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	if (GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL) != Gdiplus::Ok)
	{
		MessageBox(NULL, TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."),
		TEXT("알림"), MB_OK);
		return 0;
	}

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										
	wndClass.cbWndExtra = 0;										
	wndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));	
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				
	wndClass.hInstance = hInstance;									
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						
	wndClass.lpszClassName = WINNAME;								
	wndClass.lpszMenuName = NULL;									
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						

	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmBitsPerPel = 32;		
	dm.dmPelsWidth = 1980;		
	dm.dmPelsHeight = 1020;		
	dm.dmDisplayFrequency = 60;	

	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) 
	{
		ChangeDisplaySettings(&dm, 0);
	}

	_hWnd = CreateWindow
	(
		WINNAME,			
		WINNAME,			
		WINSTYLE,			
		WINSTART_X,			
		WINSTART_Y,			
		WINSIZE_X,			
		WINSIZE_Y,			
		NULL,				
		(HMENU)NULL,		
		hInstance,			
		NULL				
								
	);
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);


#else

	_hWnd = CreateWindow
	(
		WINNAME,				
		WINNAME,				
		WINSTYLE,				
		WINSTART_X,				
		WINSTART_Y,				
		WINSIZE_X,				
		WINSIZE_Y,				
		NULL,					
		(HMENU)NULL,			
		hInstance,				
		NULL					
								
	);
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

#endif

	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_mg->init())) 
	{
		return 0;
	}

	MSG message;

	//==================================
	SetMapMode(_mg->getHDC(), MM_ISOTROPIC);
	_cameraRc = &RectMake(0, 0, 0, 0);
	GetClientRect(_hWnd, _cameraRc);
	SetWindowExtEx(_mg->getHDC(), 960, 540, NULL);
	SetViewportExtEx(_mg->getHDC(), _cameraRc->right, _cameraRc->bottom, NULL);
	
	//==================================

	while (true) 
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) 
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else 
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}

	}

	_mg->release();
	UnregisterClass(WINNAME, hInstance);
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void SetWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0,0,width,height };
	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, 
				(rc.right - rc.left),
				(rc.bottom - rc.top),
				SWP_NOZORDER | SWP_NOMOVE);

}

#include "Stdafx.h"
#include "MainGame.h"

//=======================
// # �������� #
//=======================
HINSTANCE _hInstance;
//������ �ڵ�
HWND _hWnd;
POINT _ptMouse = { 0,0 };
MainGame* _mg;
LPRECT _cameraRc;

//================
//#�Լ� ���� ����#
//================
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void SetWindowSize(int x, int y, int width, int height);

//! window main �Լ� 
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
		MessageBox(NULL, TEXT("GDI+ ���̺귯���� �ʱ�ȭ�� �� �����ϴ�."),
		TEXT("�˸�"), MB_OK);
		return 0;
	}

	//1-1 ������â ����ü ���� �� �ʱ�ȭ
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));	//��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//���콺 Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������
	wndClass.hInstance = hInstance;									//�����츦 ������ �ĺ��� ����
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;							//Ŭ��������
	wndClass.lpszMenuName = NULL;									//�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ��Ÿ��

	//1-2. ������ Ŭ���� ���
	RegisterClass(&wndClass);

#ifdef FULLSCREEN
	//����̽� ��� ����ü (ȭ�� ���÷��� ���� ���)
	DEVMODE dm;
	ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmBitsPerPel = 32;		//32��Ʈ Ʈ���÷�
	dm.dmPelsWidth = 1980;		//�����ػ�
	dm.dmPelsHeight = 1020;		//�����ػ�
	dm.dmDisplayFrequency = 60;	//�����

	//Fields : �پ��� ���÷��� ������ �츮�� ����� �������� �Ѱ��ְڴ�.
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//ȭ���� ����Ǹ� �ڵ����� ���� ȭ���� �ػ󵵷� ����
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) 
	{
		ChangeDisplaySettings(&dm, 0);
	}

	_hWnd = CreateWindow
	(
		WINNAME,				//������ Ŭ���� �ĺ���
		WINNAME,				//������ Ÿ��Ʋ �� �̸�
		WINSTYLE,				//������ ��Ÿ��
		WINSTART_X,					//������ ȭ�� x��ǥ
		WINSTART_Y,					//������ ȭ�� Y��ǥ
		WINSIZE_X,					//������ ȭ�� ����ũ��
		WINSIZE_Y,					//������ ȭ�� ����ũ��
		NULL,					//�θ� ������ GetDesktopWindow,
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL					//�������� �ڽ� �����츦 �����ϸ� ����
								
	);
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);


#else

	//1-3. ȭ�鿡 ������ ������ â ����
	_hWnd = CreateWindow
	(
		WINNAME,				//������ Ŭ���� �ĺ���
		WINNAME,				//������ Ÿ��Ʋ �� �̸�
		WINSTYLE,				//������ ��Ÿ��
		WINSTART_X,					//������ ȭ�� x��ǥ
		WINSTART_Y,					//������ ȭ�� Y��ǥ
		WINSIZE_X,					//������ ȭ�� ����ũ��
		WINSIZE_Y,					//������ ȭ�� ����ũ��
		NULL,					//�θ� ������ GetDesktopWindow,
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL					//�������� �ڽ� �����츦 �����ϸ� ����
								
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
	//!������ Ŭ���� ��� ����
	UnregisterClass(WINNAME, hInstance);
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);

}

//������ ȭ�� ���߱�
void SetWindowSize(int x, int y, int width, int height)
{
	//Ŭ���̾�Ʈ ������
	RECT rc = { 0,0,width,height };
	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);

	//���� ��Ʈ�� ������ ������ ������ ����
	SetWindowPos(_hWnd, NULL, x, y, 
				(rc.right - rc.left),
				(rc.bottom - rc.top),
				SWP_NOZORDER | SWP_NOMOVE);// ZORDER�� ���� �ʰڴ�. �������� �ʰڴ�.

}

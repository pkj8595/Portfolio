#include "Stdafx.h"
#include "Image.h"
#include "Animation.h"


namespace my {

	//멤버 이니셜라이즈를 한이유 상속과 관계있음.
	//상속을 받은 클래스의 생성자 호출이 발생이 됨과 동시에 초기화

	Image::Image() : _imageInfo(NULL),
		_fileName(NULL),
		_isTrans(FALSE),
		_transColor(RGB(0, 0, 0)),
		_blendImage(NULL)
	{
	}

	HRESULT Image::init(int width, int height)
	{
		// 재초기화 방지 -> 이미지 정보에 값이 들어 있다면 릴리즈부터 하겠다. (포인터가 있다면 if문으로 물어보기)
		if (_imageInfo != NULL) this->release();

		//런타임	(어썰트는 false에서 동작함) >> 남발x 걸릴놈 찾을때 사용
		//assert(_imageInfo != NULL);
		//컴파일 단계에서 어썰트걸리면 죽음 -> 변수는 못잡음 상수타입들 잡을때 사용
		//static_assert

		// DC 가져오기
		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_EMPTY;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);
		_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;

		//파일 이름
		_fileName = NULL;
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);

		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}

		//DC 해제
		ReleaseDC(_hWnd, hdc);

		//런타임
		//assert(_imageInfo != NULL); (값이 들어가있다면 코드가 죽어버리먜
		//컴파일
		//static_assert
		return S_OK;
	}

	HRESULT Image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_RESOURCE;
		_imageInfo->resID = resID;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);
		_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;

		//파일 이름
		_fileName = NULL;
		_isTrans = isTrans;
		_transColor = transColor;

		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const char *fileName, int width, int height, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_FILE;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);

		_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //LR_LOADFROMFILE : 로드 리소스
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;


		int len = strlen(fileName);
		//사이즈 +1하는 이유 띄어쓰기 실수 방지
		_fileName = new CHAR[len + 1];//크기 할당(동적)
		strcpy_s(_fileName, len + 1, fileName);

		//파일 이름
		_isTrans = isTrans;
		_transColor = transColor;

		// 리소스 얻어오는데 실패했다.
		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_FILE;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);

		_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //LR_LOADFROMFILE : 로드 리소스
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->x = x;
		_imageInfo->y = y;
		_imageInfo->width = width;
		_imageInfo->height = height;


		int len = strlen(fileName);
		//사이즈 +1하는 이유 띄어쓰기 실수 방지
		_fileName = new CHAR[len + 1];//크기 할당(동적)
		strcpy_s(_fileName, len + 1, fileName);

		//파일 이름
		_isTrans = isTrans;
		_transColor = transColor;

		// 리소스 얻어오는데 실패했다.
		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_FILE;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);

		_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //LR_LOADFROMFILE : 로드 리소스
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->width = width;
		_imageInfo->height = height;
		_imageInfo->currentFrameX = 0;
		_imageInfo->currentFrameY = 0;
		_imageInfo->maxFrameX = maxFrameX - 1;
		_imageInfo->maxFrameY = maxFrameY - 1;
		_imageInfo->frameWidth = width / maxFrameX;
		_imageInfo->frameHeight = height / maxFrameY;


		int len = strlen(fileName);
		//사이즈 +1하는 이유 띄어쓰기 실수 방지
		_fileName = new CHAR[len + 1];//크기 할당(동적)
		strcpy_s(_fileName, len + 1, fileName);

		//파일 이름
		_isTrans = isTrans;
		_transColor = transColor;

		// 리소스 얻어오는데 실패했다.
		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, BOOL isTrans, COLORREF transColor)
	{
		if (_imageInfo != NULL) this->release();

		HDC hdc = GetDC(_hWnd);

		//이미지 정보 새로 생성 후 초기화
		_imageInfo = new IMAGE_INFO;
		_imageInfo->loadType = LOAD_FILE;
		_imageInfo->resID = 0;
		_imageInfo->hMemDc = CreateCompatibleDC(hdc);

		_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE); //LR_LOADFROMFILE : 로드 리소스
		_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDc, _imageInfo->hBit);
		_imageInfo->x = x;
		_imageInfo->y = y;
		_imageInfo->width = width;
		_imageInfo->height = height;
		_imageInfo->currentFrameX = 0;
		_imageInfo->currentFrameY = 0;
		_imageInfo->maxFrameX = maxFrameX - 1;
		_imageInfo->maxFrameY = maxFrameY - 1;
		_imageInfo->frameWidth = width / maxFrameX;
		_imageInfo->frameHeight = height / maxFrameY;


		int len = strlen(fileName);
		//사이즈 +1하는 이유 띄어쓰기 실수 방지
		_fileName = new CHAR[len + 1];//크기 할당(동적)
		strcpy_s(_fileName, len + 1, fileName);

		//파일 이름
		_isTrans = isTrans;
		_transColor = transColor;

		// 리소스 얻어오는데 실패했다.
		if (_imageInfo->hBit == 0)
		{
			release();
			return E_FAIL;
		}
		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	HRESULT Image::initForAlphaBlend(void)
	{
		// DC 가져오기
		HDC hdc = GetDC(_hWnd);

		_blendFunc.BlendFlags = 0;			//혼합 알파값을 사용하지 않겠다. 
		_blendFunc.AlphaFormat = 0;			//소스랑 비트맵을 혼합시킬건지
		_blendFunc.BlendOp = AC_SRC_OVER;	//비트맵을 24bit or 32bit로 쓸건지


		//이미지 정보 새로 생성 후 초기화
		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_FILE;
		_blendImage->resID = 0;
		_blendImage->hMemDc = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDc, _blendImage->hBit);
		_blendImage->width = WINSIZE_X;
		_blendImage->height = WINSIZE_Y;

		//DC 해제
		ReleaseDC(_hWnd, hdc);

		return S_OK;
	}

	void Image::setTransColor(BOOL isTrans, COLORREF transColor)
	{
		_isTrans = isTrans;
		_transColor = transColor;
	}

	void Image::release(void)
	{
		if (_imageInfo)
		{
			//이미지 삭제
			SelectObject(_imageInfo->hMemDc, _imageInfo->hOBit);
			DeleteObject(_imageInfo->hBit);
			DeleteDC(_imageInfo->hMemDc);

			SAFE_DELETE(_imageInfo);
			SAFE_DELETE_ARRAY(_fileName);

			_isTrans = FALSE;
			_transColor = RGB(0, 0, 0);
		}

		if (_blendImage)
		{
			SelectObject(_blendImage->hMemDc, _blendImage->hOBit);
			DeleteObject(_blendImage->hBit);
			DeleteDC(_blendImage->hMemDc);

			SAFE_DELETE(_blendImage);
		}
	}

	//렌더 (0, 0 지점에 렌더)
	void Image::render(HDC hdc)
	{

		if (_isTrans)
		{	
			//그려지는 순서가 느리다.
			//이미지 복사 GDI translate >> 복사가 됨 >> 해제 
			//메모리에 계속 상주하기 때문에 병목현상이 일어날수 있겠다.
			//폰노이만 아키텍처 (병목현상이 일어....나)
			//GdiTransparentBlt(): 비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
			GdiTransparentBlt
			(
				hdc,					//복사할 장소의 DC(화면에 보여줄))
				0,						//복사될 시작 좌표 X
				0,						//복사될 시작 좌표 Y
				_imageInfo->width,		//복사될 이미지 가로 크기
				_imageInfo->height,		//복사될 이미지 세로 크기
				_imageInfo->hMemDc,		//복사될 대상 메모리 DC
				0, 0,					//복사 시작 지점
				_imageInfo->width,		//복사 영역 가로 크기
				_imageInfo->height,		//복사 영역 세로 크기
				_transColor				//복사할 때 제외할 색상

			);
		}

		else
		{
			BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, SRCCOPY);
		}
	}

	void Image::render(HDC hdc, int destX, int destY)
	{
		if (_isTrans)
		{
			//GdiTransparentBlt(): 비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
			GdiTransparentBlt
			(
				hdc,					//복사할 장소의 DC (화면 DC (화면에 보여줄))
				destX,					//복사될 시작 좌표 X
				destY,					//복사될 시작 좌표 Y
				_imageInfo->width,		//복사될 이미지 가로 크기
				_imageInfo->height,		//복사될 이미지 세로 크기
				_imageInfo->hMemDc,		//복사될 대상 메모리 DC
				0, 0,					//복사 시작 지점
				_imageInfo->width,		//복사 영역 가로 크기
				_imageInfo->height,		//복사 영역 세로 크기
				_transColor				//복사할 때 제외할 색상

			);
		}

		else
		{
			//BitBit() : DC간의 영역끼리 서로 고속복사해주는 함수
			//SRCCOPY : 소스 영역을 대상 영역에 복사한다.
			BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDc, 0, 0, SRCCOPY);
		}
	}

	//클리핑
	void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
	{
		if (_isTrans)
		{
			//GdiTransparentBlt(): 비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
			GdiTransparentBlt
			(
				hdc,					//복사할 장소의 DC (화면 DC (화면에 보여줄))
				destX,					//복사될 시작 좌표 X
				destY,					//복사될 시작 좌표 Y
				sourWidth,				//복사될 이미지 가로 크기
				sourHeight,				//복사될 이미지 세로 크기
				_imageInfo->hMemDc,		//복사될 대상 메모리 DC
				sourX,					//자를 좌표 x
				sourY,					//자를 좌표 y
				sourWidth,				//자를크기
				sourHeight,				//자를크기
				_transColor				//복사할 때 제외할 색상
			);
		}

		else
		{
			BitBlt(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDc, sourX, sourY, SRCCOPY);
		}
	}

	void Image::alphaRender(HDC hdc, BYTE alpha)
	{
		//알파 블렌드를 처음 사용하는지?
		if (!_blendImage) initForAlphaBlend();

		_blendFunc.SourceConstantAlpha = alpha;

		if (_isTrans)
		{
			//1. 출력해야할 DC에 그려져있는 내용을 블렌드 이미지에 그린다.

			BitBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				hdc,
				0, 0,
				SRCCOPY
			);
			//2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다.

			GdiTransparentBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_transColor
			);
			//3. 블랜드 이미지를 화면에 그린다.
			AlphaBlend
			(
				hdc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendFunc
			);
		}
		else
		{
			// 3번 블렌드 이미지를 화면에 그린다.
			AlphaBlend
			(
				hdc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendFunc
			);
		}
	}

	void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
	{
		if (!_blendImage) initForAlphaBlend();

		_blendFunc.SourceConstantAlpha = alpha;

		if (_isTrans)
		{
			//1. 출력해야할 DC에 그려져있는 내용을 블렌드 이미지에 그린다.
			BitBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				hdc,
				destX, destY,
				SRCCOPY
			);
			//2. 원본 이미지의 배경을 없앤 후 블랜드 이미지에 그린다.
			GdiTransparentBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_transColor
			);

			AlphaBlend
			(
				hdc,
				destX, destY,
				_imageInfo->width,
				_imageInfo->height,
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendFunc
			);
			//3. 블랜드 이미지를 화면에 그린다.
		}
		else
		{
			AlphaBlend
			(
				hdc,
				destX, destY,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_blendFunc
			);
		}
	}

	void Image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
	{
		
		if (!_blendImage) initForAlphaBlend();

		_blendFunc.SourceConstantAlpha = alpha;

		if (_isTrans)
		{
			BitBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				hdc,
				0, 0,
				SRCCOPY
			);
			GdiTransparentBlt
			(
				_blendImage->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_imageInfo->hMemDc,
				0, 0,
				_imageInfo->width,
				_imageInfo->height,
				_transColor
			);
			AlphaBlend
			(
				hdc,
				destX, destY,
				sourWidth,				
				sourHeight,
				_blendImage->hMemDc,
				sourX, sourY,
				sourWidth,				
				sourHeight,
				_blendFunc
			);
			//3. 블랜드 이미지를 화면에 그린다.
		}
		else
		{
			AlphaBlend
			(
				hdc,
				destX, destY,
				sourWidth,
				sourHeight,
				_imageInfo->hMemDc,
				sourX, sourY,
				sourWidth,
				sourHeight,
				_blendFunc
			);
		}
	}

	void Image::frameRender(HDC hdc, int destX, int destY)
	{
		if (_isTrans)
		{
			//GdiTransparentBlt(): 비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
			GdiTransparentBlt
			(
				hdc,					//복사할 장소의 DC (화면 DC (화면에 보여줄))
				destX,					//복사될 시작 좌표 X
				destY,					//복사될 시작 좌표 Y
				_imageInfo->frameWidth,		//복사될 이미지 가로 크기
				_imageInfo->frameHeight,		//복사될 이미지 세로 크기
				_imageInfo->hMemDc,		//복사될 대상 메모리 DC
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,
				_imageInfo->frameWidth,	//복사 영역 가로 크기
				_imageInfo->frameHeight,		//복사 영역 세로 크기
				_transColor				//복사할 때 제외할 색상

			);
		}

		else
		{
			//BitBit() : DC간의 영역끼리 서로 고속복사해주는 함수
			//SRCCOPY : 소스 영역을 대상 영역에 복사한다.
			BitBlt(hdc, destX, destY,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
		}
	}

	void Image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
	{
		//이미지 예외처리
		_imageInfo->currentFrameX = currentFrameX;
		_imageInfo->currentFrameY = currentFrameY;
		if (currentFrameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
		if (currentFrameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}

		if (_isTrans)
		{
			//GdiTransparentBlt(): 비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
			GdiTransparentBlt
			(
				hdc,
				destX,
				destY,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight,
				_imageInfo->frameWidth,	//복사 영역 가로 크기
				_imageInfo->frameHeight,		//복사 영역 세로 크기
				_transColor				//복사할 때 제외할 색상

			);
		}

		else
		{
			BitBlt(hdc, destX, destY,
				_imageInfo->frameWidth,
				_imageInfo->frameHeight,
				_imageInfo->hMemDc,
				_imageInfo->currentFrameX * _imageInfo->frameWidth,
				_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
		}
	}

	void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
	{
		//offset 값이 음수인 경우 보정을 하겠다.
		if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
		if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

		//그려지는 영역 셋팅
		RECT rcSour;
		int sourWidth;
		int sourHeight;

		//그려지는 DC 영역 (화면크기)
		RECT rcDest;

		//그려야 할 전체 영역
		int drawAreaX = drawArea->left;
		int drawAreaY = drawArea->top;
		int drawAreaW = drawArea->right - drawArea->left;
		int drawAreaH = drawArea->bottom - drawArea->top;


		//세로 루프영역
		for (int y = 0; y < drawAreaH; y += sourHeight)
		{
			//소스 영역의 높이계산
			rcSour.top = (y + offsetY) % _imageInfo->height;
			rcSour.bottom = _imageInfo->height;
			sourHeight = rcSour.bottom - rcSour.top;

			//소스영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (y + sourHeight > drawAreaH)
			{
				//넘어간 그림의 값만큼 올려주겠다.
				rcSour.bottom -= (y + sourHeight) - drawAreaH;
				sourHeight = rcSour.bottom - rcSour.top;
			}

			//그려지는 영역 
			rcDest.top = y + drawAreaY;
			rcDest.bottom = rcDest.top + sourHeight;

			for (int x = 0; x < drawAreaW; x += sourWidth)
			{
				rcSour.left = (x + offsetX) % _imageInfo->width;
				rcSour.right = _imageInfo->width;
				sourWidth = rcSour.right - rcSour.left;

				if (x + sourWidth > drawAreaW)
				{
					rcSour.right -= (x + sourWidth) - drawAreaW;
					sourWidth = rcSour.right - rcSour.left;
				}
				rcDest.left = x + drawAreaX;
				rcDest.right = rcDest.left + sourWidth;

				render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);

			}
		}


	}

	void Image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
	{

	}
	void Image::aniRender(HDC hdc, int destX, int destY, Animation* ani)
	{
		render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
	}

	void Image::resizeRender(HDC hdc, int destX, int destY, int width, int height)
	{
		//_blendFunc.SourceConstantAlpha = 255;
		//AlphaBlend(hdc, destX, destY, width, height, _imageInfo->hMemDc,
		//	0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
		if (!_blendImage) initForAlphaBlend();
		_blendFunc.SourceConstantAlpha = 120;

		TransparentBlt
		(
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			hdc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
		TransparentBlt
		(
			_blendImage->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor
		);
		AlphaBlend
		(
			hdc,
			destX, destY,
			width,
			height,
			_imageInfo->hMemDc,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_blendFunc
		);
	}

}
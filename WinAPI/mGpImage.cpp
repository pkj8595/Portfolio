#include "Stdafx.h"
#include "mGpImage.h"

mGpImage::mGpImage():_bitmap(NULL),_bitmapInfo(NULL),_fileName(NULL)
{
}

HRESULT mGpImage::init(WCHAR *fileName, INT size, BOOL useEmbeddedColorManagement)
{
	if (_bitmapInfo != NULL) this->release();

	HDC hdc = GetDC(_hWnd);
	_bitmap = new Bitmap(fileName, useEmbeddedColorManagement);
	
	_bitmapInfo = new mGPBITMAP_INFO;
	_bitmapInfo->center_x = static_cast<INT>((-1 * (_bitmap->GetWidth() / 2)));
	_bitmapInfo->center_y = static_cast<INT>((-1 * (_bitmap->GetHeight() / 2)));
	_bitmapInfo->center_width = static_cast<INT>(_bitmap->GetWidth());
	_bitmapInfo->center_height = static_cast<INT> (_bitmap->GetHeight());
	_bitmapInfo->size = size;
	_fileName = fileName;


	_bitmapInfo->hMemDc =  CreateCompatibleDC(hdc);
	_bitmap->GetHBITMAP(Color(0, 0, 0, 0), &_bitmapInfo->hBit);
	_bitmapInfo->hOBit = (HBITMAP)SelectObject(_bitmapInfo->hMemDc, _bitmapInfo->hBit);

	if (_bitmapInfo->hBit == 0) 
	{
		release();
		return E_FAIL;
	}
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void mGpImage::render(Gdiplus::Graphics *g, int size)
{
	g->DrawImage(_bitmap, _bitmapInfo->center_x/size, _bitmapInfo->center_y/size, _bitmapInfo->center_width/size, _bitmapInfo->center_height/size);
}

void mGpImage::render(Gdiplus::Graphics *g, REAL X, REAL Y, REAL Width, REAL Height)
{
	g->DrawImage(_bitmap, X, Y, Width, Height);
}

void mGpImage::release(void)
{
	SelectObject(_bitmapInfo->hMemDc, _bitmapInfo->hOBit);
	DeleteObject(_bitmapInfo->hBit);
	DeleteDC(_bitmapInfo->hMemDc);

	SAFE_DELETE(_bitmap);
	SAFE_DELETE(_bitmapInfo);
	SAFE_DELETE_ARRAY(_fileName);
}


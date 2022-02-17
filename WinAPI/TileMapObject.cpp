#include "Stdafx.h"
#include "TileMapObject.h"

HRESULT TileMapObject::init(string filename, RECT rc, int index)
{
	_imgStr = filename;
	_lprc = rc;
	_index = index;
	_isClicked = false;
	_pt = POINT{ _lprc.left,_lprc.top };

	return S_OK;
}

void TileMapObject::release(void)
{
	//SAFE_DELETE(_lprc);
}

void TileMapObject::update(POINT pt)
{
	if (_isClicked) 
	{
		_pt = pt;
	}
}

void TileMapObject::render(HDC hdc)
{

	RectangleMakeToRECT(hdc, _lprc);
	ImgRender(hdc);

}

void TileMapObject::ImgRender(const HDC &hdc)
{
	if (_imgStr != "" && _isClicked)
	{
		IMAGEMANAGER->render(_imgStr, hdc, _pt.x, _pt.y);
	}
	else if (_imgStr != "")
	{
		IMAGEMANAGER->render(_imgStr, hdc, _lprc.left, _lprc.top);
	}
}

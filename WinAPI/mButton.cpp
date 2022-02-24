#include "Stdafx.h"
#include "mButton.h"

mButton::mButton(){
}

mButton::~mButton(){
}

HRESULT mButton::init(void)
{
	return S_OK;
}

HRESULT mButton::init(const char* filename, int x, int y)
{
	_btnImg = IMAGEMANAGER->findImage(filename);
	_x = x;
	_y = y;
	_frameX = 1;
	_btnRc = RectMakeCenter(_x, _y, _btnImg->getFrameWidth(), _btnImg->getFrameHeight());

	return S_OK;
}

void mButton::release(void)
{
}

void mButton::update(void)
{
}

void mButton::render(void)
{
	_btnImg->frameRender(getMemDC(), _btnRc.left, _btnRc.top, _frameX, 1);
}

bool mButton::isOnClick(POINT mousePt)
{
	if (!KEYMANAGER->getKeyDown()[VK_LBUTTON]){return false;}
	if (PtInRect(&_btnRc, mousePt))
	{
		return true;
	}
	return false;
}


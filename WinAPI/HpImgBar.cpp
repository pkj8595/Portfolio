#include "Stdafx.h"
#include "HpImgBar.h"

HRESULT HpImgBar::init(float* x, float* y,int width, int height, float* hp, int offsetX, int offsetY)
{
	_baseImage = new my::Image;
	_valImage = new my::Image;

	_baseImage->init("Resource/Images/Object/HpBase.bmp", width, height, TRUE, RGB(255, 0, 255));
	_valImage->init("Resource/Images/Object/HPValue.bmp", width, height, TRUE, RGB(255, 0, 255));

	_x = x;
	_y = y;
	_hp = hp;
	_maxHp = *hp;
	_offsetX = offsetX;
	_offsetY = offsetY;
	_rc = RectMakeCenter((int)*_x, (int)*_y, _baseImage->getWidth(), _baseImage->getHeight());

	return S_OK;
}

void HpImgBar::release(void)
{
	SAFE_DELETE(_baseImage);
	SAFE_DELETE(_valImage);
}

void HpImgBar::update(void)
{
	_rc = RectMakeCenter((int)*_x +_offsetX, (int)*_y + _offsetY, _baseImage->getWidth(), _baseImage->getHeight());
}

void HpImgBar::render(HDC hdc)
{
	float computeWidth = static_cast<float>(_valImage->getWidth())*
		(*_hp / _maxHp);

	_baseImage->render(hdc, _rc.left, _rc.top,0,0, _baseImage->getWidth(),_baseImage->getHeight());
	_valImage->render(hdc, _rc.left, _rc.top,0,0, static_cast<int>(computeWidth), _valImage->getHeight());

}

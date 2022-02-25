#include "Stdafx.h"
#include "Damage.h"

HRESULT Damage::init(int damage, bool isMagicDamage, float x, float y)
{
	_image = IMAGEMANAGER->addFrameImage("Damage", "Resource/Images/Lucie/CompleteImg/system/Damage.bmp", 200, 232, 10, 8, true, RGB(255, 0, 255));
	_amount = damage;
	(isMagicDamage) ? _type = 3 : _type = 0;
	_showCount = 20;
	_x = x;
	_y = y;
	_dy = 10;
	return S_OK;
}

void Damage::release(void)
{
}

void Damage::update(void)
{
	if (_dy > 0)
	{
		_y -= _dy;
		_dy--;
	}
	if (_showCount > 0) _showCount--;
}

void Damage::render(void)
{
	_image->frameRender(getMemDC(), _x, _y, _amount, _type);
}

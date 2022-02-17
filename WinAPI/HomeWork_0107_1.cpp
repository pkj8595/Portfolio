#include "Stdafx.h"
#include "HomeWork_0107_1.h"

HRESULT HomeWork_0107_1::init(void)
{
	_cannon.angle = PI / 2;		// 3.14 /2      1.78 라디안 = 90디그리 
	_cannon.length = 80;
	_cannon.radius = 50;
	_cannon.center.x = WINSIZE_X / 2;
	_cannon.center.y = WINSIZE_Y;
	_cannon.cannonAngleStart = 20 * (PI/180);
	_cannon.cannonAngleEnd = 160 * (PI/180);

	return S_OK;
}

void HomeWork_0107_1::release(void)
{
	
}

void HomeWork_0107_1::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _cannon.angle -= 0.04f;
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _cannon.angle += 0.04f;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fire();
	};

	//과제 코드 ===================================
	_count++;
	_cannon.angle += (_cannon.dir ? 0.05f : -0.05f);
	if (_count%5 == 0) 
	{
		fire();

		if (_cannon.angle < _cannon.cannonAngleStart  || _cannon.angle > _cannon.cannonAngleEnd)
		{
			_cannon.dir = (_cannon.dir ? false : true);
		}
	}
	//=============================================

	//포신 끝점의 xy좌표
	_cannon.cannonEnd.x = cosf(_cannon.angle)*_cannon.length + _cannon.center.x;
	_cannon.cannonEnd.y = -sinf(_cannon.angle)*_cannon.length + _cannon.center.y;



	for (int i = 0; i < 30; i++)
	{
		if (!_bullet[i].isFire) continue;

		_bullet[i].rc.left += 3 * cosf(_bullet[i].angle);
		_bullet[i].rc.top += 3 * -sinf(_bullet[i].angle);
		_bullet[i].rc.right += 3 * cosf(_bullet[i].angle);
		_bullet[i].rc.bottom += 3 * -sinf(_bullet[i].angle);

		if (_bullet[i].rc.bottom < 0 ||
			_bullet[i].rc.left > WINSIZE_X ||
			_bullet[i].rc.right < 0 ||
			_bullet[i].rc.top > WINSIZE_Y)
		{_bullet[i].isFire = false;}
	}

}

void HomeWork_0107_1::render(HDC hdc)
{
	//포신 그리기 
	LineMake(hdc, _cannon.center.x, _cannon.center.y, _cannon.cannonEnd.x, _cannon.cannonEnd.y);

	EllipseMakeCenter(hdc, _cannon.center.x, _cannon.center.y, _cannon.radius, _cannon.radius);

	for (int i = 0; i < 30; i++)
	{
		if (!_bullet[i].isFire) continue;
		Ellipse(hdc, _bullet[i].rc.left,
			_bullet[i].rc.top,
			_bullet[i].rc.right,
			_bullet[i].rc.bottom);
	}
	/*
		char test[120];
		wsprintf( test, " directionVecX : %d  , directionVecY : %d", sinf(_cannon.angle), cosf(_cannon.angle));
		TextOut(hdc, 0, 0, test, strlen(test));
	*/
}

void HomeWork_0107_1::fire(void)
{
	for (int i = 0; i < 30; i++)
	{
		if (_bullet[i].isFire) continue; // true >> continue
		_bullet[i].isFire = true;
		_bullet[i].angle = _cannon.angle;
		_bullet[i].rc = RectMakeCenter(_cannon.cannonEnd.x, _cannon.cannonEnd.y, 20, 20);
		break;
	}
}

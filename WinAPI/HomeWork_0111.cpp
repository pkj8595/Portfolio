#include "Stdafx.h"
#include "HomeWork_0111.h"

HRESULT HomeWork_0111::init(void)
{
	_rc = RectMakeCenter(300,300,100,100);
	_ellpt = PointMake(500, 300);
	_selectedShape = NULL_SHAPE;
	_mouseAngle = 0;
	_mouseSpeed = 0;

	//사각형의 대각선 길이
	_rcCrossDistance = sqrtf(((RECT_SIZE*0.5)*(RECT_SIZE*0.5)+ (RECT_SIZE*0.5)*(RECT_SIZE*0.5)));
	return S_OK;
}

void HomeWork_0111::release(void)
{

}

void HomeWork_0111::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) 
	{
		if (PtInRect(&_rc,_ptMouse))
		{
			_selectedShape = RECT_SHAPE;
		}
		//(x-a)*(x-a) - (y-b)*(y-b) < r*r
		if ((_ellpt.x - _ptMouse.x)*(_ellpt.x - _ptMouse.x) + (_ellpt.y - _ptMouse.y)*(_ellpt.y - _ptMouse.y) < (ELL_SIZE*0.5)*(ELL_SIZE*0.5))
		{
			_selectedShape = ELLIPSE_SHAPE;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		_selectedShape = NULL_SHAPE;
	}


	switch (_selectedShape)
	{
	case RECT_SHAPE:
		_rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, RECT_SIZE, RECT_SIZE);
		break;
	case ELLIPSE_SHAPE:
		_ellpt.x = _ptMouse.x;
		_ellpt.y = _ptMouse.y;
		break;
	default:
		break;
	}

	_mouseAngle = atan2f(_ptMouse.y - _previousMousePt.y, _ptMouse.x - _previousMousePt.x);
	_mouseSpeed = sqrt((_ptMouse.x - _previousMousePt.x) *
						(_ptMouse.x - _previousMousePt.x) +
						(_ptMouse.y - _previousMousePt.y) *
						(_ptMouse.y - _previousMousePt.y));
	//사각 -> 원충돌
	if (_selectedShape == RECT_SHAPE)
	{
		int rcCenterX = (_rc.left + _rc.right) *0.5;
		int rcCenterY = (_rc.top + _rc.bottom) *0.5;
		float centerDistance = sqrtf(((_ellpt.x - rcCenterX)*(_ellpt.x - rcCenterX)) + ((_ellpt.y - rcCenterY)*(_ellpt.y - rcCenterY)));

		if (centerDistance < _rcCrossDistance + (ELL_SIZE*0.5) &&
			(_rc.left < _ellpt.x + (ELL_SIZE*0.5) &&
				_rc.top   < _ellpt.y + (ELL_SIZE*0.5) &&
				_rc.right > _ellpt.x - (ELL_SIZE*0.5) &&
				_rc.bottom > _ellpt.y - (ELL_SIZE*0.5)))
		{

			_ellpt.x += cosf(_mouseAngle) * _mouseSpeed;
			_ellpt.y += sinf(_mouseAngle)* _mouseSpeed;
		}

	}
	//충돌 원-> 사각충돌
	else if (_selectedShape == ELLIPSE_SHAPE )
	{
		int rcCenterX = (_rc.left + _rc.right) *0.5;
		int rcCenterY = (_rc.top + _rc.bottom) *0.5;
		float centerDistance = sqrtf(((_ellpt.x - rcCenterX)*(_ellpt.x - rcCenterX)) + ((_ellpt.y - rcCenterY)*(_ellpt.y - rcCenterY)));
		
		if (centerDistance < _rcCrossDistance+ (ELL_SIZE*0.5) &&
			(_rc.left < _ellpt.x + (ELL_SIZE*0.5) &&
			_rc.top   < _ellpt.y + (ELL_SIZE*0.5) &&
			_rc.right > _ellpt.x - (ELL_SIZE*0.5) &&
			_rc.bottom > _ellpt.y - (ELL_SIZE*0.5)))
		{
			_rc.left += cosf(_mouseAngle) * _mouseSpeed;
			_rc.top += sinf(_mouseAngle)* _mouseSpeed;
			_rc.right += cosf(_mouseAngle) * _mouseSpeed;
			_rc.bottom += sinf(_mouseAngle)* _mouseSpeed;
		}
	}
	
	_previousMousePt = _ptMouse;
}

void HomeWork_0111::render(HDC hdc)
{
	//Ellipse(hdc,_rc.left,_rc.top,_rc.right,_rc.bottom);
	//EllipseMakeCenter(hdc, (_rc.left+_rc.right)*0.5, (_rc.top + _rc.bottom)*0.5,_rcCrossDistance *2, _rcCrossDistance*2);
	RectangleMakeToRECT(hdc, _rc);

	//RectangleMake(hdc, _ellpt.x - (ELL_SIZE *0.5), _ellpt.y - (ELL_SIZE *0.5), ELL_SIZE, ELL_SIZE);
	EllipseMakeCenter(hdc, _ellpt.x, _ellpt.y, ELL_SIZE, ELL_SIZE);


	char mousePointstr[124];
	_stprintf_s(mousePointstr, "x : %d , y : %d  mouseAngle : %f", _ptMouse.x, _ptMouse.y, _mouseAngle );
	TextOut(hdc, 0, 0, mousePointstr, strlen(mousePointstr));

}

bool HomeWork_0111::PtInCircle(POINT & circlePt, float round, POINT pt)
{
	if ((circlePt.x - pt.x)*(circlePt.x - pt.x) + (circlePt.y - pt.y)*(circlePt.y - pt.y) < (round*0.5)*(round*0.5))
	{
		return true;
	}
	return false;
}

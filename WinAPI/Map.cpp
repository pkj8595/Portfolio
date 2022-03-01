#include "Stdafx.h"
#include "Map.h"


HRESULT Map::init(POINT location)
{
	return S_OK;
}

void Map::release(void)
{
}

void Map::update(void)
{

}

void Map::render(void)
{

}

void Map::showMinimapIcon(int x, int y)
{
	_minimapImage->render(getMemDC(), x + _minimapImage->getWidth() * _location.x, y + _minimapImage->getHeight() * _location.y);
}

bool Map::checkActiveMap()
{
	if (*_currentMap != this)
	{
		_isActive = false;
	}
	else
	{
		_isActive = true;;
	}
	return _isActive;
}

void Map::printOutsideRC()
{
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	Rectangle(getMemDC(), _outsideRcWidth.left, _outsideRcWidth.top, _outsideRcWidth.right, _outsideRcWidth.bottom);
	Rectangle(getMemDC(), _outsideRcLength.left, _outsideRcLength.top, _outsideRcLength.right, _outsideRcLength.bottom);
	FillRect(getMemDC(), &_outsideRcWidth, brush);
	FillRect(getMemDC(), &_outsideRcLength, brush);
	DeleteObject(brush);
}

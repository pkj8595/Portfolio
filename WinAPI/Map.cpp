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

#include "Stdafx.h"
#include "StartMap.h"

HRESULT StartMap::init(POINT location)
{
	_show = true;
	_clear = true;
	_image = IMAGEMANAGER->addImage("StartGround", "Resource/Images/Lucie/CompleteImg/ground/map/Ground101.bmp", 1008, 816, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Start", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_start.bmp", 30, 30, true, RGB(255, 0, 255));
	_pixelCollisionImage = IMAGEMANAGER->addImage("StartPixel", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m101.bmp", 1008, 816, false, RGB(255, 0, 255));
	_location = location;

	_pixel = false;
	return S_OK;
}

void StartMap::release(void)
{
}

void StartMap::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pixel = !_pixel;
	}
}

void StartMap::render(void)
{
	_image->render(getMemDC());
	if (_pixel) _pixelCollisionImage->render(getMemDC());
}

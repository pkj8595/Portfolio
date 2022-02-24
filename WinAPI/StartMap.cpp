#include "Stdafx.h"
#include "StartMap.h"

HRESULT StartMap::init(POINT location)
{
	_type = Map::MAPTYPE::START;
	_show = true;
	_clear = true;
	_image = IMAGEMANAGER->addImage("StartGround", "Resource/Images/Lucie/CompleteImg/ground/map/Ground101.bmp", 1008, 816, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Start", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_start.bmp", 30, 30, true, RGB(255, 0, 255));
	_pixelCollisionImage = IMAGEMANAGER->addImage("StartPixel", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m101.bmp", 1008, 816, false, RGB(255, 0, 255));
	_upWall = IMAGEMANAGER->addImage("UpWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall2.bmp", 240, 240, true, RGB(255, 0, 255));
	_leftWall = IMAGEMANAGER->addImage("LeftWall4", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall4.bmp", 281, 600, true, RGB(255, 0, 255));
	_rightWall = IMAGEMANAGER->addImage("RightWall4", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall4.bmp", 281, 588, true, RGB(255, 0, 255));
	_downWall = IMAGEMANAGER->addImage("DownWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/downWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	
	_location = location;
	_mapRC = { 200, 50, 700, 600 };

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

	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(), 0, 2);
	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(), CENTER_X - 180, -150);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(), 728, 2);
	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(), CENTER_X - 170, _image->getHeight() - 240);
}

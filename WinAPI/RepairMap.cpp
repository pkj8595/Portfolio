#include "Stdafx.h"
#include "RepairMap.h"

HRESULT RepairMap::init(POINT location)
{
	_type = Map::MAPTYPE::REPAIR;
	_show = false;
	_clear = true;
	_image = IMAGEMANAGER->addImage("RepairGround", "Resource/Images/Lucie/CompleteImg/ground/map/ground57.bmp", 1008, 670, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Repair", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_event.bmp", 30, 30, true, RGB(255, 0, 255));
	_pixelCollisionImage = IMAGEMANAGER->addImage("RepairPixel", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m57.bmp", 1008, 670, false, RGB(255, 0, 255));
	_upWall = IMAGEMANAGER->addImage("UpWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	_leftWall = IMAGEMANAGER->addImage("LeftWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall2.bmp", 288, 480, true, RGB(255, 0, 255));
	_rightWall = IMAGEMANAGER->addImage("RightWall3", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall3.bmp", 240, 480, true, RGB(255, 0, 255));
	_downWall = IMAGEMANAGER->addImage("DownWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/downWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	_mapRC = { 200, 50, 700, 600 };
	_location = location;

	return S_OK;
}

void RepairMap::release(void)
{
}

void RepairMap::update(void)
{
}

void RepairMap::render(void)
{
	_image->render(getMemDC());

	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(), 0, 143);
	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(), CENTER_X - 180, -150);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(), 768, 143);
	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(), CENTER_X - 170, _image->getHeight() - 240);
}

#include "Stdafx.h"
#include "ChestMap.h"

HRESULT ChestMap::init(POINT location)
{
	_type = Map::MAPTYPE::TREASURE;
	_show = false;
	_clear = true;
	_image = IMAGEMANAGER->addImage("ChestGround", "Resource/Images/Lucie/CompleteImg/ground/map/Ground215.bmp", 1008, 768, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Chest", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_chest.bmp", 30, 30, true, RGB(255, 0, 255));
	_pixelCollisionImage = IMAGEMANAGER->addImage("ChestPixel", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m215.bmp",1008, 768, false, RGB(255, 0, 255));
	_upWall = IMAGEMANAGER->addImage("UpWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	_leftWall = IMAGEMANAGER->addImage("LeftWall3", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall3.bmp", 281, 540, true, RGB(255, 0, 255));
	_rightWall = IMAGEMANAGER->addImage("RightWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall2.bmp", 281, 528, true, RGB(255, 0, 255));
	_downWall = IMAGEMANAGER->addImage("DownWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/downWall1.bmp", 240, 240, true, RGB(255, 0, 255));

	_chestImage = IMAGEMANAGER->addFrameImage("Chest", "Resource/Images/Lucie/CompleteImg/object/box/$Chest.bmp", 96, 384, 1, 4, true, RGB(255, 0, 255));
	
	_open = false;
	_frameY = 0;

	_mapRC = { 200, 50, 700, 600 };
	_outsideRcWidth = { 0, 768, WINSIZE_X, WINSIZE_Y };
	_outsideRcLength = { 1008, 0, WINSIZE_X, WINSIZE_Y };
	_location = location;

	_chestEventObj = new EventObject;
	_chestEventRc = RectMakeCenter(CENTER_X, CENTER_Y + 200, 32, 32);
	_chestEventObj->init(EventObservedType::CHEST, _chestEventRc, &_isActive, 0);


	return S_OK;
}

void ChestMap::release(void)
{
	SAFE_DELETE(_chestEventObj);
}

void ChestMap::update(void)
{
	_chestRC = RectMake(CENTER_X - _chestImage->getFrameWidth(), CENTER_Y - _chestImage->getFrameHeight(), _chestImage->getFrameWidth(), _chestImage->getFrameHeight());
}

void ChestMap::render(void)
{
	_image->render(getMemDC());

	_chestImage->frameRender(getMemDC(), CENTER_X - _chestImage->getFrameWidth(), CENTER_Y - _chestImage->getFrameHeight(), 0, _frameY);
	RectangleMakeToRECT(getMemDC(), _chestEventRc);

	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(), 0, 52);
	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(), CENTER_X - 180, -150);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(), 728, 52);
	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(), CENTER_X - 170, _image->getHeight() - 240);

}

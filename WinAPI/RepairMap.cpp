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
	
	_anvilImage = IMAGEMANAGER->addFrameImage("Anvil", "Resource/Images/Lucie/CompleteImg/event/Anvil.bmp", 144, 384, 1, 4, true, RGB(255, 0, 255));
	_frameY = 0;
	_mapRC = { 200, 50, 700, 600 };
	_outsideRcWidth = { 0, 670, WINSIZE_X, WINSIZE_Y };
	_outsideRcLength = { 1008, 0, WINSIZE_X, WINSIZE_Y };
	_location = location;

	_repairEventObj = new EventObject;
	_repairEventRc = RectMakeCenter(500, 420, _anvilImage->getFrameWidth() - 30, 80);
	_repairEventObj->init(EventObservedType::ANVIL, _repairEventRc, &_isActive, 0);

	_mapRectSize = RectMake(0, 0, 1008, 670);
	_anvilFrameTime = TIMEMANAGER->getWorldTime();

	return S_OK;
}

void RepairMap::release(void)
{
	_repairEventObj->release();
	SAFE_DELETE(_repairEventObj);
}

void RepairMap::update(void)
{
	_outsideRcWidth = { 0, 670 - CAMERAMANAGER->getCameraRect().top, WINSIZE_X, WINSIZE_Y };
	_outsideRcLength = { 1008 - CAMERAMANAGER->getCameraRect().left, 0, WINSIZE_X, WINSIZE_Y };

	
}

void RepairMap::render(void)
{

	_image->render(getMemDC(),
		-CAMERAMANAGER->getCameraRect().left,
		-CAMERAMANAGER->getCameraRect().top);
	
	_anvilImage->frameRender(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - _anvilImage->getFrameWidth() + 90 - CAMERAMANAGER->getCameraRect().left,
		CAMERAMANAGER->getDisplayCenterY() - _anvilImage->getFrameHeight() + 160 - CAMERAMANAGER->getCameraRect().top, 0, _frameY);
	

	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(),
		0 - CAMERAMANAGER->getCameraRect().left,
		143 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - 80 - CAMERAMANAGER->getCameraRect().left,
		-150 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(),
		768 - CAMERAMANAGER->getCameraRect().left,
		143 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - 100 - CAMERAMANAGER->getCameraRect().left,
		_image->getHeight() - 240 - CAMERAMANAGER->getCameraRect().top);
}

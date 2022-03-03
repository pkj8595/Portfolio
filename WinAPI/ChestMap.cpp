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
	_chestEventRc = RectMakeCenter(CAMERAMANAGER->getDisplayCenterX() - 48, CAMERAMANAGER->getDisplayCenterY(), 32, 32);
	_chestEventObj->init(EventObservedType::CHEST, _chestEventRc, &_isActive, 0);


	return S_OK;
}

void ChestMap::release(void)
{
	SAFE_DELETE(_chestEventObj);
}

void ChestMap::update(void)
{
	_chestRC = RectMake(CAMERAMANAGER->getDisplayCenterX() - _chestImage->getFrameWidth(), CAMERAMANAGER->getDisplayCenterY() - _chestImage->getFrameHeight(), _chestImage->getFrameWidth(), _chestImage->getFrameHeight());
	if (_chestEventObj->getIsExcute()) openChest();
}

void ChestMap::render(void)
{
	_image->render(getMemDC(),
		- CAMERAMANAGER->getCameraRect().left,
		-CAMERAMANAGER->getCameraRect().top);

	_chestImage->frameRender(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - _chestImage->getFrameWidth() - CAMERAMANAGER->getCameraRect().left,
		CAMERAMANAGER->getDisplayCenterY() - _chestImage->getFrameHeight()- CAMERAMANAGER->getCameraRect().top, 0, _frameY);

	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(),
		0 - CAMERAMANAGER->getCameraRect().left,
		52 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - 180- -CAMERAMANAGER->getCameraRect().left,
		-150 -CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(),
		728 - CAMERAMANAGER->getCameraRect().left,
		52 -CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - 170 - CAMERAMANAGER->getCameraRect().left,
		_image->getHeight() - 240 -CAMERAMANAGER->getCameraRect().top);

}

void ChestMap::openChest(void)
{
	if (_frameY == 3) return;
	static float openTime = TIMEMANAGER->getWorldTime();
	if (openTime + 0.1f < TIMEMANAGER->getWorldTime())
	{
		if (_frameY == 1) { TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/chest.wav"); }
		_frameY++;
		openTime = TIMEMANAGER->getWorldTime();
	}
}

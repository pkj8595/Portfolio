#include "Stdafx.h"
#include "BossMap.h"

HRESULT BossMap::init(POINT location)
{
	_type = Map::MAPTYPE::BOSS;
	_show = false;
	_clear = false;
	_image = IMAGEMANAGER->addImage("BossGround", "Resource/Images/Lucie/CompleteImg/ground/map/ground95.bmp", 1104, 960, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Boss", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_boss.bmp", 30, 30, true, RGB(255, 0, 255));
	_pixelCollisionImage = IMAGEMANAGER->addImage("BossPixel", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m95.bmp", 1104, 960, false, RGB(255, 0, 255));
	_location = location;
	_outsideRcWidth = { 0, 960, WINSIZE_X, WINSIZE_Y };
	_outsideRcLength = { 1104, 0, WINSIZE_X, WINSIZE_Y };
	return S_OK;
}

void BossMap::release(void)
{
}

void BossMap::update(void)
{
}

void BossMap::render(void)
{
	_image->render(getMemDC(), -CAMERAMANAGER->getCameraRect().left, -CAMERAMANAGER->getCameraRect().top);
}

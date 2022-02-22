#include "Stdafx.h"
#include "BossMap.h"

HRESULT BossMap::init(POINT location)
{
	_show = false;
	_clear = false;
	_image = IMAGEMANAGER->addImage("BossGround", "Resource/Images/Lucie/CompleteImg/ground/map/ground95.bmp", 1104, 960, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Boss", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_boss.bmp", 30, 30, true, RGB(255, 0, 255));
	_location = location;
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
	_image->render(getMemDC());
}

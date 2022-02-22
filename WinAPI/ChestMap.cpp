#include "Stdafx.h"
#include "ChestMap.h"

HRESULT ChestMap::init(POINT location)
{
	_show = false;
	_clear = true;
	_image = IMAGEMANAGER->addImage("ChestGround", "Resource/Images/Lucie/CompleteImg/ground/map/Ground215.bmp", 1008, 768, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Chest", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_chest.bmp", 30, 30, true, RGB(255, 0, 255));
	_location = location;
	return S_OK;
}

void ChestMap::release(void)
{
}

void ChestMap::update(void)
{
}

void ChestMap::render(void)
{
	_image->render(getMemDC());
}

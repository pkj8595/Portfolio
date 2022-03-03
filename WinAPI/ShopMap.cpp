#include "Stdafx.h"
#include "ShopMap.h"


HRESULT ShopMap::init(POINT location)
{
	_type = Map::MAPTYPE::SHOP;
	_show = false;
	_clear = true;
	_image = IMAGEMANAGER->addImage("ShopGround", "Resource/Images/Lucie/CompleteImg/ground/map/ground103.bmp", 960, 576, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Shop", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_shop.bmp", 30, 30, true, RGB(255, 0, 255));
	_pixelCollisionImage = IMAGEMANAGER->addImage("ShopPixel", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m103.bmp", 960, 576, false, RGB(255, 0, 255));
	_upWall = IMAGEMANAGER->addImage("UpWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	_leftWall = IMAGEMANAGER->addImage("LeftWall5", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall5.bmp", 336, 480, true, RGB(255, 0, 255));
	_rightWall = IMAGEMANAGER->addImage("RightWall3", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall3.bmp", 240, 480, true, RGB(255, 0, 255));
	_downWall = IMAGEMANAGER->addImage("DownWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/downWall2.bmp", 288, 240, true, RGB(255, 0, 255));
	_mapRC = { 168, 50, 750, 460 };
	_outsideRcWidth = { 0, 576, CAMERAMANAGER->getDisplayAreaRight(), CAMERAMANAGER->getDisplayAreaBottom() };
	_outsideRcLength = { 960, 0, CAMERAMANAGER->getDisplayAreaRight(), CAMERAMANAGER->getDisplayAreaBottom() };
	_location = location;

	_mapRectSize = RectMake(0, 0, 960, 576);
	
	//==================================================
	_itemManager = ItemManager::getSingleton();
	_itemSpawner = ItemSpawner::getSingleton();

	_shopBar = IMAGEMANAGER->addImage("shopBar", "Resource/Images/Lucie/CompleteImg/Shop/ShopBar1.bmp", 352, 192, true, RGB(255, 0, 255));
	_shopNPC = IMAGEMANAGER->addImage("shopNPC", "Resource/Images/Lucie/CompleteImg/Shop/shop_NPC.bmp", 35, 43, true, RGB(255, 0, 255));
	
	for (int i = 0; i < ITEM_SIZE; i++)
	{
		int x = 610 + (i * 42);
		int y = 190;

		ShopEventObj eventObj;
		eventObj.itemObj =_itemSpawner->createItemMapInit(x, y, false,this);
		eventObj.eventObj = new EventObject;
		eventObj.eventObj->init(EventObservedType::SHOP, RectMakeCenter(x, y+60, 32, 32),&_isActive, eventObj.itemObj->getItemIndex());
		_rcEvent[i] = RectMakeCenter(x, y + 60, 32, 32);

		_vObj.push_back(eventObj);
	}

	return S_OK;
}

void ShopMap::release(void)
{
	
	for (; _viObj != _vObj.end(); ++_viObj)
	{
		SAFE_DELETE((*_viObj).eventObj);
	}
}

void ShopMap::update(void)
{
	_viObj = _vObj.begin();
	for (; _viObj != _vObj.end(); ++_viObj) 
	{
		if (!(*_viObj).eventObj->getIsRemoveObserver())
		{
			(*_viObj).itemObj->setIsActive(false);
			SAFE_DELETE((*_viObj).eventObj);
			_vObj.erase(_viObj);
			break;
		}
	}

	_outsideRcWidth = { 0 - CAMERAMANAGER->getCameraRect().left, 576 - CAMERAMANAGER->getCameraRect().top, 1104, 960 };

	_outsideRcLength = { 960 - CAMERAMANAGER->getCameraRect().left, 0 - CAMERAMANAGER->getCameraRect().top, 1104,960 };


}

void ShopMap::render(void)
{
	_image->render(getMemDC(),
		-CAMERAMANAGER->getCameraRect().left,
		-CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(),
		-28 - CAMERAMANAGER->getCameraRect().left,
		122 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(),
		 510 - CAMERAMANAGER->getCameraRect().left,
		-100 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(),
		758 - CAMERAMANAGER->getCameraRect().left,
		35 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(),
		352 - CAMERAMANAGER->getCameraRect().left,
		465 - CAMERAMANAGER->getCameraRect().top);
	//============================================
	_shopNPC->render(getMemDC(),
		680 - CAMERAMANAGER->getCameraRect().left,
		140 - CAMERAMANAGER->getCameraRect().top);
	_shopBar->render(getMemDC(),
		530 - CAMERAMANAGER->getCameraRect().left,
		40 - CAMERAMANAGER->getCameraRect().top);

}

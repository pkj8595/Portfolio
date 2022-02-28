#include "Stdafx.h"
#include "ShopMap.h"
#include "ItemManager.h"
#include "ItemSpawner.h"


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
	_location = location;

	//==================================================
	_itemManager = ItemManager::getSingleton();
	_itemSpawner = ItemSpawner::getSingleton();

	for (int i = 0; i < ITEM_SIZE; i++)
	{
		_itemIndex[i] =_itemSpawner->createItemMapInit(610+(i*42), 190, false,this);
	}
	
	_shopCollider = RectMake(_x, _y, 32, 32);

	_shopBar = IMAGEMANAGER->addImage("shopBar", "Resource/Images/Lucie/CompleteImg/Shop/ShopBar1.bmp", 352, 192, true, RGB(255, 0, 255));
	_shopNPC = IMAGEMANAGER->addImage("shopNPC", "Resource/Images/Lucie/CompleteImg/Shop/shop_NPC.bmp", 35, 43, true, RGB(255, 0, 255));
	_x = CENTER_X;
	_y = CENTER_Y;

	return S_OK;
}

void ShopMap::release(void)
{
}

void ShopMap::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y--;
		cout << "x: " << _x << ", y: " << _y << endl;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y++;
		cout << "x: " << _x << ", y: " << _y << endl;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x--;
		cout << "x: " << _x << ", y: " << _y << endl;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x++;
		cout << "x: " << _x << ", y: " << _y << endl;
	}

	_shopCollider = RectMakeCenter(_x, _y, 32, 32);

}

void ShopMap::render(void)
{
	_image->render(getMemDC());
	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(), -28, 122);
	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(), CENTER_X - 180, -150);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(), 758, 35);
	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(), 352, 465);
	//============================================
	_shopNPC->render(getMemDC(), 680, 140);
	_shopBar->render(getMemDC(), 530, 40);


	RectangleMakeToRECT(getMemDC(),_shopCollider);

}

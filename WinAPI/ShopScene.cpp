#include "Stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init(void)
{
	//_itemManager = new ItemManager;
	//_itemManager->init();
	_inven = new Inventory;
	_inven->init();
	return S_OK;
}

void ShopScene::release(void)
{
	//_itemManager->release();
	_inven->release();
}

void ShopScene::update(void)
{
	//_itemManager->update();
	_inven->update();
}

void ShopScene::render(void)
{
	//_itemManager->render();
	_inven->render();
}

#include "Stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init(void)
{
	_itemManager = new ItemManager;
	_itemManager->init();
	return S_OK;
}

void ShopScene::release(void)
{
	_itemManager->release();
}

void ShopScene::update(void)
{
	_itemManager->update();
}

void ShopScene::render(void)
{
	_itemManager->render();
}

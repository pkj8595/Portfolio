#include "Stdafx.h"
#include "ItemManager.h"

HRESULT ItemManager::init(void)
{
	IMAGEMANAGER->addFrameImage("ItemImage", "Resource/Images/Lucie/CompleteImg/item/Item_Image.bmp", 320, 256, 10, 8, true, RGB(255, 0, 255));

	_index = 0;
	return S_OK;
}

void ItemManager::setItemList()
{
	_index++;
	Item* temp = new Item;
	temp->setItemData(_index, EITEM_TYPE::ENPTY, "È­¿°°Ë", "È­¿°°ËÀÌ´Ù.", 1, 0, 100);
	temp->setItemAttribute(0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0);
	_vItem.push_back(temp);
}

void ItemManager::release(void)
{
}

void ItemManager::update(void)
{
}

void ItemManager::render(void)
{
}

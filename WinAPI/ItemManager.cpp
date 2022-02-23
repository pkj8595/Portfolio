#include "Stdafx.h"
#include "ItemManager.h"

HRESULT ItemManager::init(void)
{
	_itemImg = IMAGEMANAGER->addFrameImage("ItemImage", "Resource/Images/Lucie/CompleteImg/item/Item_Image.bmp", 320, 256, 10, 8, true, RGB(255, 0, 255));

	vector<string> vData = TEXTDATAMANAGER->loadFstream("Resource/Text/ITEM_DATA.csv");

	if (vData.size() % 19 == 0)
	{
		for (int i = 0; i < vData.size(); i += 19)
		{
			Item* item = new Item;
			item->_index = atoi(vData[i].c_str());
			item->_imgNum = atoi(vData[i + 1].c_str());
			item->_type = static_cast<EITEM_TYPE>(atoi(vData[i + 2].c_str()));
			item->_name = vData[i + 3].c_str();
			item->_description = vData[i + 4].c_str();
			item->_equip_level = atoi(vData[i + 5].c_str());
			item->_price = atoi(vData[i + 6].c_str());
			item->_attribute._hp = atoi(vData[i + 7].c_str());
			item->_attribute._maxHp = atoi(vData[i + 8].c_str());
			item->_attribute._mana = atoi(vData[i + 9].c_str());
			item->_attribute._maxMana = atoi(vData[i + 10].c_str());
			item->_attribute._critical = atoi(vData[i + 11].c_str());
			item->_attribute._offencePower = atoi(vData[i + 12].c_str());
			item->_attribute._magicPower = atoi(vData[i + 13].c_str());
			item->_attribute._speed = atoi(vData[i + 14].c_str());
			item->_attribute._attackSpeed = atoi(vData[i + 15].c_str());
			item->_attribute._damageBalace = atoi(vData[i + 16].c_str());
			item->_attribute._experience = atoi(vData[i + 17].c_str());
			item->_attribute._stamina = atoi(vData[i + 18].c_str());

			_vItem.push_back(item);
		}
		cout << "ItemManager::init(void) >> item data init ok" << endl;
	}
	return S_OK;
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

Item* ItemManager::getItem(int imgIndex)
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem)->_imgNum == imgIndex)
		{
			return *_viItem;
		}
	}

	cout << "ItemManager::getItem() >> fail" << endl;
	return nullptr;
}

inline void ItemManager::itemImgRender(int imgIndex, int x, int y)
{
	int destX = imgIndex / 10;
	int destY = imgIndex % 10;
	IMAGEMANAGER->findImage("ItemImage")->frameRender(getMemDC(),x,y, destX, destY);
}

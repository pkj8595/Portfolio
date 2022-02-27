#include "Stdafx.h"
#include "ItemManager.h"


ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}


HRESULT ItemManager::init(void)
{
	_itemImg = IMAGEMANAGER->addFrameImage("ItemImage", "Resource/Images/Lucie/CompleteImg/item/Item_Image.bmp", 320, 256, 10, 8, true, RGB(255, 0, 255));
	//_itemImg = IMAGEMANAGER->addImage("ItemImage", "Resource/Images/Lucie/CompleteImg/item/Item_Image.bmp", 320, 256,  true, RGB(255, 0, 255));
	_bigItemImg = IMAGEMANAGER->addFrameImage("bigItemImg", "Resource/Images/Lucie/CompleteImg/item/Item_Image.bmp", 640, 512, 10, 8, true, RGB(255, 0, 255));

	vector<string> vData = TEXTDATAMANAGER->loadFstream("Resource/Text/ITEM_DATA.csv");

	if (vData.size() % 22 == 0)
	{
		for (int i = 0; i < vData.size(); i += 22)
		{
			Item* item = new Item;
			item->_index = atoi(vData[i].c_str());
			item->_imgNum = atoi(vData[i + 1].c_str());
			item->_type = static_cast<EITEM_TYPE>(atoi(vData[i + 2].c_str()));
			item->_name = vData[i + 3].c_str();
			item->_description = vData[i + 4].c_str();
			item->_equip_level = atoi(vData[i + 5].c_str());
			item->_price = atoi(vData[i + 6].c_str());
			item->_durability = atoi(vData[i + 7].c_str());
			item->_maxDurability = atoi(vData[i + 8].c_str());
			item->_attribute._hp = atoi(vData[i + 9].c_str());
			item->_attribute._maxHp = atoi(vData[i + 10].c_str());
			item->_attribute._mana = atoi(vData[i + 11].c_str());
			item->_attribute._maxMana = atoi(vData[i + 12].c_str());
			item->_attribute._critical = atoi(vData[i + 13].c_str());
			item->_attribute._offencePower = atoi(vData[i + 14].c_str());
			item->_attribute._magicPower = atoi(vData[i + 15].c_str());
			item->_attribute._speed = atof(vData[i + 16].c_str());
			item->_attribute._attackSpeed = atoi(vData[i + 17].c_str());
			item->_attribute._damageBalance = atoi(vData[i + 18].c_str());
			item->_attribute._experience = atoi(vData[i + 19].c_str());
			item->_attribute._stamina = atoi(vData[i + 20].c_str());
			item->_attribute._maxStamina = atoi(vData[i + 21].c_str());

			//item->toString();
			_vItem.push_back(item);
		}
		cout << "ItemManager::init(void) >> item data init ok" << endl;
	}

	vector<string> vEnchantData = TEXTDATAMANAGER->loadFstream("Resource/Text/ENCHANT_DATA.csv");

	if (vEnchantData.size() % 19 == 0)
	{
		for (int i = 0; i < vEnchantData.size(); i += 19)
		{
			EnchantItem* enchantItem = new EnchantItem;
			enchantItem->_index = atoi(vEnchantData[i].c_str());
			enchantItem->_name = vEnchantData[i + 1].c_str();
			enchantItem->_equip_level = atoi(vEnchantData[i + 2].c_str());
			enchantItem->_durability = atoi(vEnchantData[i + 3].c_str());
			enchantItem->_maxDurability = atoi(vEnchantData[i + 4].c_str());
			enchantItem->_enchantStr = vEnchantData[i+5].c_str();
			enchantItem->_attribute._hp = atoi(vEnchantData[i + 6].c_str());
			enchantItem->_attribute._maxHp = atoi(vEnchantData[i + 7].c_str());
			enchantItem->_attribute._mana = atoi(vEnchantData[i + 8].c_str());
			enchantItem->_attribute._maxMana = atoi(vEnchantData[i + 9].c_str());
			enchantItem->_attribute._critical = atoi(vEnchantData[i + 10].c_str());
			enchantItem->_attribute._offencePower = atoi(vEnchantData[i + 11].c_str());
			enchantItem->_attribute._magicPower = atoi(vEnchantData[i + 12].c_str());
			enchantItem->_attribute._speed = atof(vEnchantData[i + 13].c_str());
			enchantItem->_attribute._attackSpeed = atoi(vEnchantData[i + 14].c_str());
			enchantItem->_attribute._damageBalance = atoi(vEnchantData[i + 15].c_str());
			enchantItem->_attribute._experience = atoi(vEnchantData[i + 16].c_str());
			enchantItem->_attribute._stamina = atoi(vEnchantData[i + 17].c_str());
			enchantItem->_attribute._maxStamina = atoi(vEnchantData[i + 18].c_str());

			//enchantItem->toString();
			_vEnchantItem.push_back(enchantItem);
		}
		cout << "ItemManager::init(void) >> item enchant data init ok" << endl;
	}

	return S_OK;
}
	
void ItemManager::release(void)
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		SAFE_DELETE(*_viItem);
	}

	_viEnchantItem = _vEnchantItem.begin();
	for (; _viEnchantItem != _vEnchantItem.end(); ++_viEnchantItem)
	{
		SAFE_DELETE(*_viEnchantItem);
	}
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

Item* ItemManager::getItemIndex(int index)
{
	if (index >= _vItem.size()) return nullptr;
	return _vItem[index];
}

void ItemManager::getItemImgRender(HDC hdc,int imgIndex, int x, int y)
{
	int destY = 0; 
	int destX = 0;
	destY = (imgIndex-1) / 10;
	destX = (imgIndex-1) % 10;

	_itemImg->frameRender(hdc, x, y, destX, destY);
}

void ItemManager::getBigItemImgRender(HDC hdc,int imgIndex, int x, int y)
{
	int destY = 0;
	int destX = 0;
	destY = (imgIndex - 1) / 10;
	destX = (imgIndex - 1) % 10;

	_bigItemImg->frameRender(hdc, x, y, destX, destY);
}

void ItemManager::getItemIndexRender(HDC hdc, int index, int x, int y)
{
	if (index >= _vItem.size()) return;
	int imgIndex = _vItem[index]->_imgNum;
	int destY = 0;
	int destX = 0;
	destY = (imgIndex - 1) / 10;
	destX = (imgIndex - 1) % 10;

	_bigItemImg->frameRender(hdc, x, y, destX, destY);
}

void ItemManager::getBigItemIndexRender(HDC hdc, int index, int x, int y)
{
	if (index >= _vItem.size()) return;
	int imgIndex = _vItem[index]->_imgNum;
	int destY = 0;
	int destX = 0;
	destY = (imgIndex - 1) / 10;
	destX = (imgIndex - 1) % 10;

	_bigItemImg->frameRender(hdc, x, y, destX, destY);
}

EnchantItem* ItemManager::getEnchantItem()
{
	return _vEnchantItem[RND->getInt(_vEnchantItem.size() - 1)];
}

#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	_itemManager = new ItemManager;
	_itemManager->init();

	_inventoryBackground = IMAGEMANAGER->addImage("inventoryBackground", "Resource/Images/Lucie/CompleteImg/inventory/inventoryBackground.bmp", 240, 296, true, RGB(255, 0, 255));
	_combineBackground.img = IMAGEMANAGER->addImage("combineBackground", "Resource/Images/Lucie/CompleteImg/inventory/combineBackground.bmp", 180, 180, true, RGB(255, 0, 255));
	_inventoryGoldIcon.img = IMAGEMANAGER->addImage("inventoryGoldIcon", "Resource/Images/Lucie/CompleteImg/inventory/inventoryGoldIcon.bmp", 22, 22, true, RGB(255, 0, 255));
	_inventoryHintCorner.img = IMAGEMANAGER->addImage("inventoryHintCorner", "Resource/Images/Lucie/CompleteImg/inventory/inventoryHintCorner.bmp", 21, 21, true, RGB(255, 0, 255));
	_inventoryClickHelp.img = IMAGEMANAGER->addImage("inventoryClickHelp", "Resource/Images/Lucie/CompleteImg/inventory/inventoryClickHelp.bmp", 21, 21, true, RGB(255, 0, 255));

	_combineBtnIcon2.img = IMAGEMANAGER->addFrameImage("combineBtnIcon2", "Resource/Images/Lucie/CompleteImg/inventory/combineBtnIcon2.bmp", 240, 27,3,1, true, RGB(255, 0, 255));
	_inventoryCloseBtn.img = IMAGEMANAGER->addFrameImage("inventoryCloseBtn", "Resource/Images/Lucie/CompleteImg/inventory/inventoryCloseBtn.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	_inventorySlot.img = IMAGEMANAGER->addFrameImage("InventorySlot", "Resource/Images/Lucie/CompleteImg/inventory/InventorySlot.bmp", 76, 38, 2, 1, true, RGB(255, 0, 255));
	_inventorySlotA.img = IMAGEMANAGER->addFrameImage("InventorySlotA", "Resource/Images/Lucie/CompleteImg/inventory/InventorySlotA.bmp", 76, 38, 2, 1, true, RGB(255, 0, 255));
	_inventorySlotB.img = IMAGEMANAGER->addFrameImage("inventorySlotB", "Resource/Images/Lucie/CompleteImg/inventory/inventorySlotB.bmp", 76, 38, 2, 1, true, RGB(255, 0, 255));

	//_btn = new mButton;
	//_btn->init();
	_x = WINSIZE_X - _inventoryBackground->getWidth()-30;
	_y = WINSIZE_Y * 0.5 - 200;

	_rc = RectMake(_x, _y, _inventoryBackground->getWidth(), _inventoryBackground->getHeight());

	_combineBackground.pt = PointMake(_rc.left - 178, _rc.top + 100);
	_combineBtnIcon2.pt = PointMake(_rc.left - 120, _rc.top + 240);
	_inventoryGoldIcon.pt = PointMake(_rc.left + 160, _rc.top + 260);
	_inventoryHintCorner.pt = PointMake(_rc.left + 100, _rc.top + 100);
	_inventoryClickHelp.pt = PointMake(_rc.left + 100, _rc.top + 100);
	_inventoryCloseBtn.pt = PointMake(_rc.left + 100, _rc.top + 100);
	_inventorySlot.pt = PointMake(_rc.left + 100, _rc.top + 100);
	_inventorySlotA.pt = PointMake(_rc.left + 100, _rc.top + 100);
	_inventorySlotB.pt = PointMake(_rc.left + 100, _rc.top + 100);

	_emptyItem = new Item;
	_equipWeapon = _emptyItem;
	_equipArmor = _emptyItem;
	_equipShoes = _emptyItem;

	for (int i = 0; i < 30; i++)
	{
		int temp = RND->getInt(34);
		pushItem(_itemManager->getItemIndex(temp));
	}

	return S_OK;
}

void Inventory::release(void)
{
	SAFE_DELETE(_itemManager);
	SAFE_DELETE(_emptyItem);

	//_btn->release();
}

void Inventory::update(void)
{
	//_btn->update();
}

void Inventory::render(void)
{
	renderInventoryBase();
	showInventoryItem();
	showAbilityItem();
	//_btn->render();
}

void Inventory::renderInventoryBase()
{
	_combineBackground.img->render(getMemDC(), _combineBackground.pt.x, _combineBackground.pt.y);
	_inventoryBackground->render(getMemDC(), _rc.left, _rc.top);
	_inventoryGoldIcon.img->render(getMemDC(), _inventoryGoldIcon.pt.x, _inventoryGoldIcon.pt.y);
	_inventoryHintCorner.img->render(getMemDC(), _inventoryHintCorner.pt.x, _inventoryHintCorner.pt.y);
	_inventoryClickHelp.img->render(getMemDC(), _inventoryClickHelp.pt.x, _inventoryClickHelp.pt.y);
	//framerender
	_combineBtnIcon2.img->frameRender(getMemDC(), _combineBtnIcon2.pt.x, _combineBtnIcon2.pt.y,1,1);
	_inventoryCloseBtn.img->frameRender(getMemDC(), _inventoryCloseBtn.pt.x, _inventoryCloseBtn.pt.y, 1, 1);
	_inventorySlot.img->frameRender(getMemDC(), _inventorySlot.pt.x, _inventorySlot.pt.y, 1, 1);
	_inventorySlotA.img->frameRender(getMemDC(), _inventorySlotA.pt.x, _inventorySlotA.pt.y, 1, 1);
	_inventorySlotB.img->frameRender(getMemDC(), _inventorySlotB.pt.x, _inventorySlotB.pt.y, 1, 1);
}

Item* Inventory::getEquipWeapon()
{
	if (_equipWeapon)
	{
		return _equipWeapon;
	}
	return nullptr;
}

//아이템이 벡터에 들어올때마다 실행시켜서 총합산 데미지를 최신화한다.
void Inventory::computeItemTotalAttribute()
{
	cout << "Inventory::computeItemTotalAttribute" << endl;
	CPlayer_Attribute temp;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		cout << (*_viItem)->_imgNum <<(*_viItem)->_name<< endl;
		if ((*_viItem)->_type == EITEM_TYPE::ABILITY)
		{
			temp = temp + (*_viItem)->_attribute;
		}
	}
	if (_equipWeapon) { temp = temp + _equipWeapon->_attribute; }
	if (_equipArmor) { temp = temp + _equipArmor->_attribute; }
	if (_equipShoes) { temp = temp + _equipShoes->_attribute; }

	_totalAttribute = temp;
}

void Inventory::pushItem(Item* item)
{
	_vItem.push_back(item);
	computeItemTotalAttribute();
}

void Inventory::showInventoryItem()
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem)->_type != EITEM_TYPE::ABILITY)
		{
			
		}
	}
}

void Inventory::showAbilityItem()
{
	int count=0;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem)->_type == EITEM_TYPE::ABILITY)
		{
			_itemManager->getItemImgRender((*_viItem)->_imgNum, ABILITY_IMG_X + (count* ABILITY_IMG_OFFSET), ABILITY_IMG_Y);
			count++;
		}
	}
}

#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	_itemManager = ItemManager::getSingleton();

	_inventoryBackground = IMAGEMANAGER->addImage("inventoryBackground", "Resource/Images/Lucie/CompleteImg/inventory/inventoryBackground.bmp", 240, 296, true, RGB(255, 0, 255));
	_inventoryGoldIcon.img = IMAGEMANAGER->addImage("inventoryGoldIcon", "Resource/Images/Lucie/CompleteImg/inventory/inventoryGoldIcon.bmp", 22, 22, true, RGB(255, 0, 255));
	_inventoryCloseBtn.img = IMAGEMANAGER->addFrameImage("inventoryCloseBtn", "Resource/Images/Lucie/CompleteImg/inventory/inventoryCloseBtn.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
	_inventorySlot.img = IMAGEMANAGER->addFrameImage("InventorySlot", "Resource/Images/Lucie/CompleteImg/inventory/InventorySlot.bmp", 76, 38, 2, 1, true, RGB(255, 0, 255));
	_inventorySlotB.img = IMAGEMANAGER->addFrameImage("inventorySlotB", "Resource/Images/Lucie/CompleteImg/inventory/inventorySlotB.bmp", 76, 38, 2, 1, true, RGB(255, 0, 255));
	_itemInfoWindow.img = IMAGEMANAGER->addImage("ItemInfoWindow", "Resource/Images/Lucie/CompleteImg/inventory/ItemInfoWindow.bmp", 300,210);

	_x = CAMERAMANAGER->getDisplayAreaRight() - _inventoryBackground->getWidth()-30;
	_y = CAMERAMANAGER->getDisplayAreaBottom() * 0.5 - 200;

	_rc = RectMake(_x, _y, _inventoryBackground->getWidth(), _inventoryBackground->getHeight());

	
	_inventoryGoldIcon.pt = PointMake(_rc.left + 160, _rc.top + 260);
	_goldRc = RectMake(CAMERAMANAGER->getDisplayAreaRight() - 200, 0, 128, 32);
	_inventoryCloseBtn.pt = PointMake(_rc.left + 205, _rc.top + 15);
	_inventorySlot.pt = PointMake(_rc.left + 25, _rc.top + 50);
	_inventorySlotB.pt = PointMake(_rc.left + 100, _rc.top + 100);

	_statusTextPos = PointMake(_rc.left + 25 , _rc.top+170);

	_rcCloseBtn = RectMake(_inventoryCloseBtn.pt.x, _inventoryCloseBtn.pt.y, _inventoryCloseBtn.img->getFrameWidth(), _inventoryCloseBtn.img->getFrameHeight());

	_emptyItem = new Item;
	_equipWeapon= _emptyItem;
	_equipArmor = _emptyItem;
	_equipShoes = _emptyItem;
	_equipHat	= _emptyItem;

	_isShowInven = false;
	_abilutyItemCount = 0;
	_invenItemCount = 0;

	_ptotalAttribute = nullptr;
	_pAttribute = nullptr;

	_pushItmeWorldTime = TIMEMANAGER->getWorldTime();
	_isShowGetItem = false;
	
	_enchantSuccessWorldTime = TIMEMANAGER->getWorldTime();
	_isExcuteEnchant = false;
	_isEnchantSuccess = false;
	_enchantStr = "";

	_gold = 150;
	_isInventoryFull =_againTakeAbilityItem = _isDestroy = _isRepair = _isbuyItemfail = false;
	_messageWorldTime = TIMEMANAGER->getWorldTime();

	_messageRc = RectMakeCenter(CAMERAMANAGER->getDisplayCenterX(), -(CAMERAMANAGER->getDisplayCenterY()*0.4), 32, 32);

	return S_OK;
}

void Inventory::release(void)
{
	SAFE_DELETE(_itemManager);
	SAFE_DELETE(_emptyItem);

}

void Inventory::update(void)
{
	//마우스가 이미지 렉트 위에 올라가면 프레임이 바뀌어야함
	checkMouseEvent();
	if (KEYMANAGER->isOnceKeyDown('I')) { _isShowInven = !_isShowInven; }
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		int temp = RND->getInt(34);
		//_itemManager->getItemIndex(temp)->toString();
		pushItem(_itemManager->getItemIndex(temp));
	}
}

void Inventory::render(void)
{
	if (_isShowInven)
	{
		renderInventoryBase();
		equipRender();
		showInventoryItem();
		renderInvenAttributeText();

		RECT goldRc = RectMakeCenter(_rc.left + 198, _rc.top + 276, 32, 32);
		string goldStr = to_string(_gold);
		inventorydrawText(goldStr, goldRc, 20, RGB(0, 0, 0),false);

		if (PtInRect(&_rcCloseBtn, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isShowInven = false;
			}
		}
	}

	if (_isShowGetItem)
	{
		renderPushItemMassege();
	}
	if (_isExcuteEnchant)
	{
		if (TIMEMANAGER->getWorldTime() < _enchantSuccessWorldTime + 1.0f)
		{
			
			inventorydrawText(_enchantStr, _messageRc, 50, RGB(255, 255, 255),true);
		}
		else
		{
			_isEnchantSuccess = false;
			_isExcuteEnchant = false;
		}
	}
	if (_isbuyItemfail || _isDestroy|| _againTakeAbilityItem|| _isRepair|| _isInventoryFull)
	{
		if (TIMEMANAGER->getWorldTime() < _messageWorldTime + MESSAGE_SHOW_TIME)
		{
			if (_isbuyItemfail) { _messageStr = "돈이.. 부족하다....."; }
			else if (_isDestroy) { _messageStr = "내 무기가.. 부서졌다..."; }
			else if (_againTakeAbilityItem)
			{
				_messageStr = "이건.. 이미 있어.";
			}
			else if (_isRepair)
			{
				_messageStr = "무기가 반짝거린다.";
			}
			else if (_isInventoryFull)
			{
				_messageStr = "가방이 가득 찼어.";
			}
			inventorydrawText(_messageStr, _messageRc, 50, RGB(255, 255, 255),true);
		}
		else
		{
			_isbuyItemfail = false;
			_isDestroy = false;
			_againTakeAbilityItem = false;
			_isRepair = false;
			_isInventoryFull = false;
		}
	}

	//우측 상단 gold text
	_goldStr =  to_string(_gold)+ " Gold" ;
	inventorydrawText(_goldStr, _goldRc, 30, RGB(255,255, 255), false);

	renderItemInfoWindow();
	showAbilityItem();

}

void Inventory::renderInventoryBase()
{
	_inventoryBackground->render(getMemDC(), _rc.left, _rc.top);
	_inventoryGoldIcon.img->render(getMemDC(), _inventoryGoldIcon.pt.x, _inventoryGoldIcon.pt.y);
	
	_inventoryCloseBtn.img->frameRender(getMemDC(), _inventoryCloseBtn.pt.x, _inventoryCloseBtn.pt.y, 1, 1);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_inventorySlot.img->frameRender(getMemDC(),
				_inventorySlot.pt.x+ INVENTORY_IMG_OFFSETX *j,
				_inventorySlot.pt.y+ INVENTORY_IMG_OFFSETY *i, 1, 1);
		}
	}
	
	char str[32] = "인벤토리";
	FONTMANAGER->drawText(getMemDC(), _rc.left +98, _rc.top + 18, "야놀자 야체 Regular", 20, 200, str, strlen(str), RGB(255, 255, 255));
	
}

//아이템이 벡터에 들어올때마다 실행시켜서 총합산 데미지를 최신화한다.
void Inventory::computeItemTotalAttribute()
{
	CPlayer_Attribute temp;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first->_type == EITEM_TYPE::ABILITY)
		{
			temp = temp + (*_viItem).first->_attribute;
		}
	}
	if (_equipWeapon) { temp = temp + _equipWeapon->_attribute; }
	if (_equipArmor) { temp = temp + _equipArmor->_attribute; }
	if (_equipShoes) { temp = temp + _equipShoes->_attribute; }
	if (_equipHat) { temp = temp + _equipHat->_attribute; }

	_itemTotalAttribute = temp;
}

bool Inventory::buyItem(int num)
{
	Item* item = _itemManager->getItemIndex(num);
	if (item->_price < _gold)
	{
		_gold -= item->_price;
		pushItem(item);
		return true;
	}
	else
	{
		cout << "돈 부족" << endl;
		_isbuyItemfail = true;
		_messageWorldTime = TIMEMANAGER->getWorldTime();
		return false;
	}

}

void Inventory::pushItem(Item* item)
{
	if (item->_type == EITEM_TYPE::ABILITY)
	{
		_viItem = _vItem.begin();
		for (; _viItem != _vItem.end(); ++_viItem)
		{
			if ((*_viItem).first->_index == item->_index)
			{
				_againTakeAbilityItem = true;
				_messageWorldTime = TIMEMANAGER->getWorldTime();
				return;
			}
		}
		RECT temp = RectMake(
			ABILITY_IMG_X + (_abilutyItemCount* ABILITY_IMG_OFFSET),
			CAMERAMANAGER->getDisplayAreaBottom()-50,
			32, 32);
		_vItem.push_back(make_pair(item, temp));
		updatePushItemMassege(item);
		_abilutyItemCount++;
	}
	else if (checkIsFullInventory())
	{
		return;
	}
	else if (item->_type == EITEM_TYPE::EQUIP_WEAPON_BOW||
			item->_type == EITEM_TYPE::EQUIP_WEAPON_SWORD||
			item->_type == EITEM_TYPE::EQUIP_HAT||
			item->_type == EITEM_TYPE::EQUIP_ARMOR||
			item->_type == EITEM_TYPE::EQUIP_SHOES)
	{
		Item* copyItem = new Item;
		*copyItem = *item;
		RECT tempRc = RectMake(
			_inventorySlot.pt.x + 3 + (INVENTORY_IMG_OFFSETX * (_invenItemCount % 5)),
			_inventorySlot.pt.y + 3 + (INVENTORY_IMG_OFFSETY * (_invenItemCount / 5)),
			32, 32);
		_vItem.push_back(make_pair(copyItem, tempRc));
		updatePushItemMassege(item);
		_invenItemCount++;
	}
	else
	{
		RECT tempRc = RectMake(
			_inventorySlot.pt.x + 3 + (INVENTORY_IMG_OFFSETX * (_invenItemCount % 5)),
			_inventorySlot.pt.y + 3 + (INVENTORY_IMG_OFFSETY * (_invenItemCount / 5)),
			32, 32);
		_vItem.push_back(make_pair(item, tempRc));
		updatePushItemMassege(item);
		_invenItemCount++;
	}

	computeItemTotalAttribute();
}

bool Inventory::checkIsFullInventory()
{
	int asize = 0;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first->_type == EITEM_TYPE::ABILITY)
		{
			asize++;
		}
	}
	if (_vItem.size() - asize > INVENTORY_SIZE - 1)
	{
		_isInventoryFull = true;
		_messageWorldTime = TIMEMANAGER->getWorldTime();
		return true;
	}
	return false;
}

void Inventory::pushItem(int num)
{
	pushItem(_itemManager->getItemIndex(num));
}

void Inventory::updatePushItemMassege(Item* item)
{
	_showGetItemImgNum = item->_imgNum;
	_isShowGetItem = true;
	_pushItmeWorldTime = TIMEMANAGER->getWorldTime();
}

void Inventory::showInventoryItem()
{
	int countInven = 0;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first->_type == EITEM_TYPE::ABILITY) continue;
		_itemManager->getItemInvenImgRender(getMemDC(),(*_viItem).first->_imgNum,
			_inventorySlot.pt.x +3+ (INVENTORY_IMG_OFFSETX * (countInven % 5)),
			_inventorySlot.pt.y +3+ (INVENTORY_IMG_OFFSETY * (countInven / 5)));
		countInven++;
	}
}

void Inventory::showAbilityItem()
{
	int countAbility = 0;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first->_type != EITEM_TYPE::ABILITY)continue;

		_itemManager->getItemImgRender(getMemDC(), (*_viItem).first->_imgNum,
			ABILITY_IMG_X + (countAbility* ABILITY_IMG_OFFSET),
			(CAMERAMANAGER->getDisplayAreaBottom() - 50));
		countAbility++;
	}
}


void Inventory::checkMouseEvent(void)
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if (PtInRect(&(*_viItem).second, _ptMouse))
		{

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				cout << (*_viItem).first->_name << endl;
				switch ((*_viItem).first->_type)
				{
				case EITEM_TYPE::POTION:
					*_pAttribute = *_pAttribute + (*_viItem).first->_attribute;
					_vItem.erase(_viItem);
					computeRect();
					break;
				case EITEM_TYPE::MATERIAL:
					_vItem.erase(_viItem);
					computeRect();
					break;
				case EITEM_TYPE::SCROLL:
					_isExcuteEnchant = true;
					_isEnchantSuccess = false;
					_enchantSuccessWorldTime = TIMEMANAGER->getWorldTime();
					switch ((*_viItem).first->_index)
					{
					case 5:
						//armor
						if (_equipArmor != _emptyItem)
						{
							_isEnchantSuccess = _equipArmor->getEnchantedItem(*_itemManager->getEnchantItem());
						}
						break;
					case 6:
						//shoes
						if (_equipShoes != _emptyItem)
						{
							_isEnchantSuccess = _equipShoes->getEnchantedItem(*_itemManager->getEnchantItem());
						}
						break;
					case 7:
						//weapon
						if (_equipWeapon != _emptyItem)
						{
							_isEnchantSuccess = _equipWeapon->getEnchantedItem(*_itemManager->getEnchantItem());
						}
						break;
					case 8:
						//hat
						if (_equipHat != _emptyItem)
						{
							_isEnchantSuccess = _equipHat->getEnchantedItem(*_itemManager->getEnchantItem());
						}
						break;
					}
					
					if (_isEnchantSuccess)
					{
						_enchantStr = "강화 성공";
						_vItem.erase(_viItem);
						computeRect();
					}
					else
					{
						_enchantStr = "강화 실패";
					}
					break;

				case EITEM_TYPE::ABILITY:
					break;
				case EITEM_TYPE::EQUIP_WEAPON_BOW:
					setEquipWeapon((*_viItem).first);
					break;
				case EITEM_TYPE::EQUIP_WEAPON_SWORD:
					setEquipWeapon((*_viItem).first);
					break;
				case EITEM_TYPE::EQUIP_ARMOR:
					setEquipArmor((*_viItem).first);
					break;
				case EITEM_TYPE::EQUIP_HAT:
					setEquipHat((*_viItem).first);
					break;
				case EITEM_TYPE::EQUIP_SHOES:
					setEquipShoes((*_viItem).first);
					break;
				default:
					break;
				}
				break;
			}
			//아이템 버리기
			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON)) 
			{
				if ((*_viItem).first->_type != EITEM_TYPE::ABILITY)
				{
					cout<< (*_viItem).first->_name<<endl;
					if ((*_viItem).first->_type == EITEM_TYPE::EQUIP_WEAPON_BOW ||
						(*_viItem).first->_type == EITEM_TYPE::EQUIP_WEAPON_SWORD||
						(*_viItem).first->_type == EITEM_TYPE::EQUIP_HAT||
						(*_viItem).first->_type == EITEM_TYPE::EQUIP_ARMOR||
						(*_viItem).first->_type == EITEM_TYPE::EQUIP_SHOES)
					{
						if (_equipWeapon == (*_viItem).first) { _equipWeapon = _emptyItem; }
						if (_equipArmor == (*_viItem).first) { _equipArmor = _emptyItem; }
						if (_equipShoes == (*_viItem).first) { _equipShoes = _emptyItem; }
						if (_equipHat == (*_viItem).first) { _equipHat = _emptyItem; }
						SAFE_DELETE((*_viItem).first);
					}
					_vItem.erase(_viItem);
					computeRect();
					computeItemTotalAttribute();
					break;
					//todo 드랍아이템 생성
				}
			}
		}
	}
}

void Inventory::computeRect(void)
{
	_abilutyItemCount = 0;
	_invenItemCount = 0;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first->_type == EITEM_TYPE::ABILITY) 
		{
			RECT temp = RectMake(
				(CAMERAMANAGER->getDisplayAreaRight()*0.2) + (_abilutyItemCount* ABILITY_IMG_OFFSET),
				CAMERAMANAGER->getDisplayAreaBottom()-100,
				32, 32);
			(*_viItem).second = temp;
			_abilutyItemCount++;
		}
		else
		{
			RECT temp = RectMake(
				_inventorySlot.pt.x + 3 + (INVENTORY_IMG_OFFSETX * (_invenItemCount % 5)),
				_inventorySlot.pt.y + 3 + (INVENTORY_IMG_OFFSETY * (_invenItemCount / 5)),
				32, 32);
			(*_viItem).second = temp;
			_invenItemCount++;
		}
	}
	
}

void Inventory::renderPushItemMassege()
{
	int x = ((_showGetItemImgNum - 1) % 10) * 64;
	int y = ((_showGetItemImgNum - 1) / 10) * 64;

	string str;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first->_imgNum == _showGetItemImgNum)
		{
			str = (*_viItem).first->_name.c_str();
			break;
		}
	}
	RECT massageRc = RectMakeCenter(CAMERAMANAGER->getDisplayCenterX(), CAMERAMANAGER->getDisplayCenterY() - (CAMERAMANAGER->getDisplayCenterY()*0.4), str.size()*17,100);

	inventorydrawText(str, massageRc,50,RGB(255,255,255),true);

	IMAGEMANAGER->findImage("bigItemImg")->render(getMemDC(), massageRc.left - 64, massageRc.top - 10, x, y, 64, 64);
	if (TIMEMANAGER->getWorldTime() > _pushItmeWorldTime + PUSH_ITEM_MESSAGE)
	{
		_isShowGetItem = false;
	}

}

void Inventory::inventorydrawText(std::string &str, const RECT &massgeRc, int fontsize, COLORREF color,bool isCenter)
{
	char* cstr = new char[str.size() + 1];
	copy(str.begin(), str.end(), cstr);
	cstr[str.size()] = '\0';

	if (isCenter)
	{
		FONTMANAGER->drawTextRectCenter(getMemDC(), massgeRc, "야놀자 야체 Regular", fontsize, 200, cstr, strlen(cstr), color);
	}
	else
	{
		FONTMANAGER->drawText(getMemDC(), massgeRc, "야놀자 야체 Regular", fontsize, 200, cstr, strlen(cstr), color);
	}

	delete[] cstr;
}

void Inventory::renderInvenAttributeText(void)
{
	if (!_ptotalAttribute) return;
	string script[8];

	script[0] = "최대체력 : " + to_string(_ptotalAttribute->_maxHp);
	script[1] = "공격력 : " + to_string((int)_ptotalAttribute->_offencePower);
	script[2] = "마법력 : " + to_string((int)_ptotalAttribute->_magicPower);
	script[3] = "이동속도 : "; 
	char speedStr[16];
	sprintf_s(speedStr, "%.1f", (float)_ptotalAttribute->_speed);
	script[3] = script[3] + speedStr;
	script[4] = "최대마나 : " + to_string(_ptotalAttribute->_maxMana);
	script[5] = "공격속도 : " + to_string((int)_ptotalAttribute->_attackSpeed);
	script[6] = "데미지밸런스 : " + to_string((int)_ptotalAttribute->_damageBalance);
	script[7] = "치명타 : " + to_string((int)_ptotalAttribute->_critical);

	for (int i = 0; i < 8; i++)
	{
		char* str = new char[script[i].size() + 1];
		copy(script[i].begin(), script[i].end(), str);
		str[script[i].size()] = '\0';

		FONTMANAGER->drawText(getMemDC(), (int)_statusTextPos.x+((int)i / 4)*90, (int)_statusTextPos.y+(20*((int)i%4)), "야놀자 야체 Regular", 20, 200, str, strlen(str), RGB(0, 0, 0));

		delete[] str;
	}

}

void Inventory::equipRender(void)
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first == _equipWeapon||
			(*_viItem).first == _equipArmor ||
			(*_viItem).first == _equipShoes||
			(*_viItem).first == _equipHat)
		{
			_inventorySlotB.img->frameRender(getMemDC(), (*_viItem).second.left-3, (*_viItem).second.top-3, 1, 1);
		}
	}

}

void Inventory::renderItemInfoWindow()
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		//인벤토리가 꺼져있고 
		if (!_isShowInven)
		{
			if ((*_viItem).first->_type != EITEM_TYPE::ABILITY) continue;
		}
		if (PtInRect(&(*_viItem).second, _ptMouse))
		{
			int rcX;
			int rcY;
			if ((*_viItem).first->_type == EITEM_TYPE::ABILITY)
			{
				rcX = (*_viItem).second.left - 300;
				rcY = (*_viItem).second.top - 175;
			}
			else
			{
				rcX = (*_viItem).second.left - 300;
				rcY = (*_viItem).second.top + 20;
			}
			
			_itemInfoWindow.img->alphaRender(getMemDC(), rcX, rcY, 230);

			InfoWindowText itemInfo[6];

			itemInfo[0].str = (*_viItem).first->_name;
			itemInfo[0].pt = PointMake(rcX+15, rcY+12);
			itemInfo[0].fontSize = 30;
			itemInfo[0].color = RGB(255,255,255);

			itemInfo[1].str = (*_viItem).first->_description;
			char form = '^';
			char to = '\n';
			replace(itemInfo[1].str.begin(), itemInfo[1].str.end(), form, to);
			itemInfo[1].pt = PointMake(rcX+15, rcY+150);
			itemInfo[1].fontSize = 20;
			itemInfo[1].color = RGB(255, 255, 255);

			itemInfo[2].str = changeItemTypeToStr((*_viItem).first->_type);
			itemInfo[2].pt = PointMake(rcX+100, rcY+45);
			itemInfo[2].fontSize = 25;
			itemInfo[2].color = RGB(125, 60, 120);

			if ((*_viItem).first->_durability != 0)
			{
				itemInfo[3].str = to_string((*_viItem).first->_durability) + "/" + to_string((*_viItem).first->_maxDurability);
				itemInfo[3].pt = PointMake(rcX + 200, rcY + 50);
			}
			if ((*_viItem).first->_enchantStr != "")
			{
				itemInfo[4].str = "추가된 효과 : "+(*_viItem).first->_enchantStr;
				itemInfo[4].pt = PointMake(rcX + 15, rcY + 190);
				itemInfo[4].fontSize = 15;
				itemInfo[4].color = RGB(0, 200,0);
			}

			itemInfo[5].str = changeAttributeToStr((*_viItem).first->_attribute);
			itemInfo[5].pt = PointMake(rcX + 100, rcY + 70);
			itemInfo[5].fontSize = 20;
			itemInfo[5].color = RGB(190, 190, 160);

			_itemManager->getBigItemInvenImgRender(getMemDC(), (*_viItem).first->_imgNum, rcX + 15, rcY + 60);

			

			for (int i = 0; i < 6; i++)
			{
				char* str = new char[itemInfo[i].str.size() + 1];
				copy(itemInfo[i].str.begin(), itemInfo[i].str.end(), str);
				str[itemInfo[i].str.size()] = '\0';

				FONTMANAGER->drawText(getMemDC(), (int)itemInfo[i].pt.x, (int)itemInfo[i].pt.y, "야놀자 야체 Regular", itemInfo[i].fontSize, 300, str, strlen(str), itemInfo[i].color);

				delete[] str;
			}
			break;

		}
	}

}

void Inventory::removeItem(Item* item)
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first == item)
		{
			if ((*_viItem).first->_type != EITEM_TYPE::ABILITY)
			{
				cout << (*_viItem).first->_name << endl;
				if ((*_viItem).first->_type == EITEM_TYPE::EQUIP_WEAPON_BOW ||
					(*_viItem).first->_type == EITEM_TYPE::EQUIP_WEAPON_SWORD ||
					(*_viItem).first->_type == EITEM_TYPE::EQUIP_HAT ||
					(*_viItem).first->_type == EITEM_TYPE::EQUIP_ARMOR ||
					(*_viItem).first->_type == EITEM_TYPE::EQUIP_SHOES)
				{
					if (_equipWeapon == (*_viItem).first) { _equipWeapon = _emptyItem; }
					if (_equipArmor == (*_viItem).first) { _equipArmor = _emptyItem; }
					if (_equipShoes == (*_viItem).first) { _equipShoes = _emptyItem; }
					if (_equipHat == (*_viItem).first) { _equipHat = _emptyItem; }
					SAFE_DELETE((*_viItem).first);
				}
				_vItem.erase(_viItem);
				computeRect();
				computeItemTotalAttribute();
				break;
			}
		}
	}
}

string Inventory::changeItemTypeToStr(EITEM_TYPE type)
{
	string str;
	switch (type)
	{	
	case EITEM_TYPE::EMPTY:
		str = "";
		break;
	case EITEM_TYPE::POTION:
		str = "포션";
		break;
	case EITEM_TYPE::SCROLL:
		str = "스크롤";
		break;
	case EITEM_TYPE::ABILITY:
		str = "어빌리티";
		break;
	case EITEM_TYPE::EQUIP_WEAPON_BOW:
		str = "활";
		break;
	case EITEM_TYPE::EQUIP_WEAPON_SWORD:
		str = "검";
		break;
	case EITEM_TYPE::EQUIP_ARMOR:
		str = "갑옷";
		break;
	case EITEM_TYPE::EQUIP_HAT:
		str = "모자";
		break;
	case EITEM_TYPE::EQUIP_SHOES:
		str = "신발";
		break;
	case EITEM_TYPE::MATERIAL:
		str = "재료";
		break;
	default:
		break;
	}
	return str;
}

string Inventory::changeAttributeToStr(CPlayer_Attribute attri)
{
	string str = "";
	if (attri._hp != 0) str = str + " 체력" + (attri._hp > 0 ? "+" : "") + to_string((int)attri._hp) + '\n';
	if (attri._maxHp != 0) str = str + " 최대체력" + (attri._maxHp > 0 ? "+" : "") + to_string((int)attri._maxHp) + '\n';
	if (attri._mana != 0) str = str + " 마나" + (attri._mana > 0 ? "+" : "") + to_string((int)attri._mana) + '\n';
	if (attri._maxMana != 0) str = str + " 최대마나" + (attri._maxMana > 0 ? "+" : "") + to_string((int)attri._maxMana) + '\n';
	if (attri._critical != 0) str = str + " 치명타확률" + (attri._critical > 0 ? "+" : "") + to_string((int)attri._critical) + "%\n";
	if (attri._offencePower != 0) str = str + " 공격력" + (attri._offencePower > 0 ? "+" : "") + to_string((int)attri._offencePower) + '\n';
	if (attri._magicPower != 0) str = str + " 마법력" + (attri._magicPower > 0 ? "+" : "") + to_string((int)attri._magicPower) + '\n';
	if (attri._speed != 0) 
	{ 
		char num[16];
		sprintf_s(num, "%.2f", attri._speed);
		str = str + " 이동속도" + (attri._speed > 0 ? "+" : "") + num + '\n';
	}
	if (attri._damageBalance != 0) str = str + " 데미지밸런스" + (attri._damageBalance > 0 ? "+" : "") + to_string((int)attri._damageBalance) + "%\n";
	if (attri._experience != 0) str = str + " 경험치" + (attri._experience > 0 ? "+" : "") + to_string((int)attri._experience) + '\n';
	if (attri._maxStamina != 0) str = str + " 스테미나 회복률" + (attri._maxStamina > 0 ? "-" : "") + to_string((int)attri._maxStamina) + "%\n";
	//if (attri._maxExperience != 0) str = str +" "+ to_string((int)attri._maxExperience)+'\n';
	//if (attri._attackSpeed	 != 0) str = str +" 공격속도"+ to_string((int)attri._attackSpeed	) +'\n';
	//if (attri._maxStamina	 != 0) str = str +" "+ to_string((int)attri._maxStamina	) +'\n';
	
	return str;
}

void Inventory::decreaseDurability(int dufault)
{
	if (_equipWeapon != _emptyItem)
	{
		(*_equipWeapon)._durability -= dufault;
		if ((*_equipWeapon)._durability < 0)
		{
			removeItem(_equipWeapon);
			_isDestroy = true;
			_messageWorldTime = TIMEMANAGER->getWorldTime();
		}
	}

}

bool Inventory::repairWeapon(int gold)
{
	if (_gold > gold)
	{
		_gold -= gold;
		_equipWeapon->_durability = _equipWeapon->_maxDurability;
		_isRepair = true;
		_messageWorldTime = TIMEMANAGER->getWorldTime();
		return true;
	}
	else
	{
		_isbuyItemfail = true;
		_messageWorldTime = TIMEMANAGER->getWorldTime();
		return false;
	}
	
}

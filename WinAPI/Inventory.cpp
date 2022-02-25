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
	_itemInfoWindow.img = IMAGEMANAGER->addImage("ItemInfoWindow", "Resource/Images/Lucie/CompleteImg/inventory/ItemInfoWindow.bmp", 300,200);

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
	_inventoryCloseBtn.pt = PointMake(_rc.left + 205, _rc.top + 15);
	_inventorySlot.pt = PointMake(_rc.left + 25, _rc.top + 50);
	_inventorySlotA.pt = PointMake(_rc.left + 100, _rc.top + 100);
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
	//���콺�� �̹��� ��Ʈ ���� �ö󰡸� �������� �ٲ�����
	//_btn->update();
	checkMouse();
	if (KEYMANAGER->isOnceKeyDown('I')) { _isShowInven = !_isShowInven; }
	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		int temp = RND->getInt(34);
		_itemManager->getItemIndex(temp)->toString();
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
		showAttributeText();

		if (PtInRect(&_rcCloseBtn, _ptMouse))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_isShowInven = false;
			}
		}
	}

	renderItemInfo();
	showAbilityItem();

}

void Inventory::renderInventoryBase()
{
	_combineBackground.img->render(getMemDC(), _combineBackground.pt.x, _combineBackground.pt.y);
	_inventoryBackground->render(getMemDC(), _rc.left, _rc.top);
	_inventoryGoldIcon.img->render(getMemDC(), _inventoryGoldIcon.pt.x, _inventoryGoldIcon.pt.y);
	_inventoryHintCorner.img->render(getMemDC(), _inventoryHintCorner.pt.x, _inventoryHintCorner.pt.y);
	_inventoryClickHelp.img->render(getMemDC(), _inventoryClickHelp.pt.x, _inventoryClickHelp.pt.y);
	//frame render
	_combineBtnIcon2.img->frameRender(getMemDC(), _combineBtnIcon2.pt.x, _combineBtnIcon2.pt.y,1,1);
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
	//_inventorySlotA.img->frameRender(getMemDC(), _inventorySlotA.pt.x, _inventorySlotA.pt.y, 1, 1);
	//_inventorySlotB.img->frameRender(getMemDC(), _inventorySlotB.pt.x, _inventorySlotB.pt.y, 1, 1);

}

Item** Inventory::getEquipWeapon()
{
	return &_equipWeapon;
}


//�������� ���Ϳ� ���ö����� ������Ѽ� ���ջ� �������� �ֽ�ȭ�Ѵ�.
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

void Inventory::pushItem(Item* item)
{
	if (item->_type == EITEM_TYPE::ABILITY)
	{
		_viItem = _vItem.begin();
		for (; _viItem != _vItem.end(); ++_viItem)
		{
			if ((*_viItem).first->_index == item->_index) { return; }
		}
		RECT temp = RectMake(
			ABILITY_IMG_X + (_abilutyItemCount* ABILITY_IMG_OFFSET),
			ABILITY_IMG_Y,
			32, 32);
		_vItem.push_back(make_pair(item, temp));
		_abilutyItemCount++;
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
		_invenItemCount++;
	}
	else
	{
		RECT tempRc = RectMake(
			_inventorySlot.pt.x + 3 + (INVENTORY_IMG_OFFSETX * (_invenItemCount % 5)),
			_inventorySlot.pt.y + 3 + (INVENTORY_IMG_OFFSETY * (_invenItemCount / 5)),
			32, 32);
		_vItem.push_back(make_pair(item, tempRc));
		_invenItemCount++;
	}
	computeItemTotalAttribute();
}

void Inventory::showInventoryItem()
{
	int countInven = 0;
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		if ((*_viItem).first->_type == EITEM_TYPE::ABILITY) continue;
		_itemManager->getItemImgRender((*_viItem).first->_imgNum,
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

		_itemManager->getItemImgRender((*_viItem).first->_imgNum,
			ABILITY_IMG_X + (countAbility* ABILITY_IMG_OFFSET),
			ABILITY_IMG_Y);
		countAbility++;
	}
}


void Inventory::checkMouse(void)
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
			//������ ������
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
					//todo ��������� ����
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
				ABILITY_IMG_X + (_abilutyItemCount* ABILITY_IMG_OFFSET),
				ABILITY_IMG_Y,
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

void Inventory::showAttributeText(void)
{
	if (!_ptotalAttribute) return;
	string script[8];

	script[0] = "�ִ�ü�� : " + to_string(_ptotalAttribute->_maxHp);
	script[1] = "���ݷ� : " + to_string((int)_ptotalAttribute->_offencePower);
	script[2] = "������ : " + to_string((int)_ptotalAttribute->_magicPower);
	script[3] = "�̵��ӵ� : "; 
	char speedStr[16];
	sprintf_s(speedStr, "%.1f", (float)_ptotalAttribute->_speed);
	script[3] = script[3] + speedStr;
	script[4] = "�ִ븶�� : " + to_string(_ptotalAttribute->_maxMana);
	script[5] = "���ݼӵ� : " + to_string((int)_ptotalAttribute->_attackSpeed);
	script[6] = "�������뷱�� : " + to_string((int)_ptotalAttribute->_damageBalance);
	script[7] = "ġ��Ÿ : " + to_string((int)_ptotalAttribute->_critical);

	for (int i = 0; i < 8; i++)
	{
		char* str = new char[script[i].size() + 1];
		copy(script[i].begin(), script[i].end(), str);
		str[script[i].size()] = '\0';

		FONTMANAGER->drawText(getMemDC(), (int)_statusTextPos.x+((int)i / 4)*90, (int)_statusTextPos.y+(20*((int)i%4)), "�߳��� ��ü Regular", 20, 200, str, strlen(str), RGB(0, 0, 0));

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

void Inventory::renderItemInfo()
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		//�κ��丮�� �����ְ� 
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
			if ((*_viItem).first->_equip_level != 0)
			{
				itemInfo[4].str = "+"+to_string((*_viItem).first->_equip_level);
				itemInfo[4].pt = PointMake(rcX+50, rcY+12);
				itemInfo[4].fontSize = 30;
				itemInfo[4].color = RGB(125, 60,120);
			}

			itemInfo[5].str = changeAttributeToStr((*_viItem).first->_attribute);
			itemInfo[5].pt = PointMake(rcX + 100, rcY + 70);
			itemInfo[5].fontSize = 20;
			itemInfo[5].color = RGB(190, 190, 160);

			_itemManager->getBigItemImgRender((*_viItem).first->_imgNum, rcX + 15, rcY + 60);
			for (int i = 0; i < 6; i++)
			{
				char* str = new char[itemInfo[i].str.size() + 1];
				copy(itemInfo[i].str.begin(), itemInfo[i].str.end(), str);
				str[itemInfo[i].str.size()] = '\0';

				FONTMANAGER->drawText(getMemDC(), (int)itemInfo[i].pt.x, (int)itemInfo[i].pt.y, "�߳��� ��ü Regular", itemInfo[i].fontSize, 300, str, strlen(str), itemInfo[i].color);

				delete[] str;
			}
			break;

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
		str = "����";
		break;
	case EITEM_TYPE::SCROLL:
		str = "��ũ��";
		break;
	case EITEM_TYPE::ABILITY:
		str = "�����Ƽ";
		break;
	case EITEM_TYPE::EQUIP_WEAPON_BOW:
		str = "Ȱ";
		break;
	case EITEM_TYPE::EQUIP_WEAPON_SWORD:
		str = "��";
		break;
	case EITEM_TYPE::EQUIP_ARMOR:
		str = "����";
		break;
	case EITEM_TYPE::EQUIP_HAT:
		str = "����";
		break;
	case EITEM_TYPE::EQUIP_SHOES:
		str = "�Ź�";
		break;
	case EITEM_TYPE::MATERIAL:
		str = "���";
		break;
	default:
		break;
	}
	return str;
}

string Inventory::changeAttributeToStr(CPlayer_Attribute attri)
{
	string str = "";
	if (attri._hp != 0) str = str + " ü��" + (attri._hp > 0 ? "+" : "") + to_string((int)attri._hp) + '\n';
	if (attri._maxHp != 0) str = str + " �ִ�ü��" + (attri._maxHp > 0 ? "+" : "") + to_string((int)attri._maxHp) + '\n';
	if (attri._mana != 0) str = str + " ����" + (attri._mana > 0 ? "+" : "") + to_string((int)attri._mana) + '\n';
	if (attri._maxMana != 0) str = str + " �ִ븶��" + (attri._maxMana > 0 ? "+" : "") + to_string((int)attri._maxMana) + '\n';
	if (attri._critical != 0) str = str + " ġ��ŸȮ��" + (attri._critical > 0 ? "+" : "") + to_string((int)attri._critical) + "%\n";
	if (attri._offencePower != 0) str = str + " ���ݷ�" + (attri._offencePower > 0 ? "+" : "") + to_string((int)attri._offencePower) + '\n';
	if (attri._magicPower != 0) str = str + " ������" + (attri._magicPower > 0 ? "+" : "") + to_string((int)attri._magicPower) + '\n';
	if (attri._speed != 0) 
	{ 
		char num[16];
		sprintf_s(num, "%.2f", attri._speed);
		str = str + " �̵��ӵ�" + (attri._speed > 0 ? "+" : "") + num + '\n';
	}
	if (attri._damageBalance != 0) str = str + " �������뷱��" + (attri._damageBalance > 0 ? "+" : "") + to_string((int)attri._damageBalance) + "%\n";
	if (attri._experience != 0) str = str + " ����ġ" + (attri._experience > 0 ? "+" : "") + to_string((int)attri._experience) + '\n';
	if (attri._stamina != 0) str = str + " ���׹̳� ȸ����" + (attri._stamina > 0 ? "+" : "") + to_string((int)attri._stamina) + "%\n";
	//if (attri._maxExperience != 0) str = str +" "+ to_string((int)attri._maxExperience)+'\n';
	//if (attri._attackSpeed	 != 0) str = str +" ���ݼӵ�"+ to_string((int)attri._attackSpeed	) +'\n';
	//if (attri._maxStamina	 != 0) str = str +" "+ to_string((int)attri._maxStamina	) +'\n';
	
	return str;
}

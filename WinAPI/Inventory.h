#pragma once
#include "GameNode.h"
#include "mButton.h"
#include "ItemManager.h"

#define	ABILITY_IMG_OFFSET		50
#define	ABILITY_IMG_X			300
#define	ABILITY_IMG_Y			(WINSIZE_Y-50)

#define	INVENTORY_IMG_OFFSETX		40
#define	INVENTORY_IMG_OFFSETY		40

class Inventory : public GameNode
{
	typedef struct STInvenPos
	{
		my::Image* img;
		POINT pt;			//offset
	}InvenPos;

	typedef struct STInvenPosBtn
	{
		my::Image* img;
		POINT pt;			//offset
		RECT rc;
		int frameX;
	}InvenPosBtn;

	ItemManager* _itemManager;
	my::Image* _inventoryBackground;
	RECT _rc;
	int _x, _y;
	InvenPos _combineBackground;
	InvenPos _inventoryGoldIcon;
	InvenPos _inventoryHintCorner;
	InvenPos _inventoryClickHelp;
	InvenPosBtn _combineBtnIcon2;
	InvenPosBtn _inventoryCloseBtn;
	RECT _rcCloseBtn;
	InvenPos _inventorySlot;
	InvenPos _inventorySlotA;
	InvenPos _inventorySlotB;

	//=================================
	vector<pair<Item*, RECT>> _vItem;
	vector<pair<Item*, RECT>>::iterator _viItem;

	Item* _equipWeapon;		//장착중인 무기
	Item* _equipArmor;		//장착중인 아머
	Item* _equipShoes;		//장착중인 신발
	Item* _equipHat;		//장착중인 신발

	Item* _emptyItem;		//빈 아이템

	CPlayer_Attribute _itemTotalAttribute;	//총 아이템 능력치
	CPlayer_Attribute* _ptotalAttribute;	//아이템 + 플레이어
	CPlayer_Attribute* _pAttribute;			//플레이어 능력치

	bool _isShowInven;
	int _abilutyItemCount;
	int _invenItemCount;

	POINT _statusTextPos;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renderInventoryBase(void);
	void showInventoryItem(void);
	void showAbilityItem(void);

	void setPTotalattribute(CPlayer_Attribute* att)
	{
		_ptotalAttribute = att;
	}
	void setPlayerAttribute(CPlayer_Attribute* att)
	{
		_pAttribute = att;
	}

	//==========================
	// ### Player Equipment ###
	//==========================
	//인벤토리 아이템 추가
	void pushItem(Item* item);
	//총 아이템 능력치 합산
	void computeItemTotalAttribute();
	//장착중인 무기 반환
	Item** getEquipWeapon();

	CPlayer_Attribute getItemTotalAttribute(){return _itemTotalAttribute;}

	void setEquipWeapon(Item* witem)
	{
		if (_equipWeapon == _emptyItem) _equipWeapon = witem;
		else if (_equipWeapon != _emptyItem) _equipWeapon = _emptyItem;
		computeItemTotalAttribute();
	}
	void setEquipArmor(Item* aitem)
	{
		if (_equipArmor == _emptyItem) _equipArmor = aitem;
		else if (_equipArmor != _emptyItem) _equipArmor = _emptyItem;
		computeItemTotalAttribute();
	}
	void setEquipShoes(Item* sitem)
	{
		if (_equipShoes == _emptyItem) _equipShoes = sitem;
		else if (_equipShoes != _emptyItem) _equipShoes = _emptyItem;
		computeItemTotalAttribute();
	}
	void setEquipHat(Item* hitem)
	{
		if(_equipHat== _emptyItem) _equipHat = hitem;
		else if (_equipHat != _emptyItem) _equipHat = _emptyItem;
		computeItemTotalAttribute();
	}

	void checkMouse(void);
	void computeRect(void);

	bool getIsShowInven(void) { return _isShowInven; }
	void setIsShowInven(bool isShowInven) { _isShowInven = isShowInven; }
	void showAttributeText(void);
};


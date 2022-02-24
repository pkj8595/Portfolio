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

	ItemManager* _itemManager;
	my::Image* _inventoryBackground;
	RECT _rc;
	int _x, _y;
	InvenPos _combineBackground;
	InvenPos _inventoryGoldIcon;
	InvenPos _inventoryHintCorner;
	InvenPos _inventoryClickHelp;
	InvenPos _combineBtnIcon2;
	InvenPos _inventoryCloseBtn;
	InvenPos _inventorySlot;
	InvenPos _inventorySlotA;
	InvenPos _inventorySlotB;

	//=================================
	vector<pair<Item*,RECT>> _vItem;
	vector<pair<Item*, RECT>>::iterator _viItem;

	Item* _equipWeapon;		//장착중인 무기
	Item* _equipArmor;		//장착중인 아머
	Item* _equipShoes;		//장착중인 신발
	Item* _equipHat;		//장착중인 신발
	Item* _emptyItem;		//빈 아이템

	CPlayer_Attribute _totalAttribute;	//총 아이템 능력치

	bool _isShowInven;
	int _abilutyItemCount;
	int _invenItemCount;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renderInventoryBase();
	void showInventoryItem();
	void showAbilityItem();


	//==========================
	// ### Player Equipment ###
	//==========================
	//인벤토리 아이템 추가
	void pushItem(Item* item);
	//총 아이템 능력치 합산
	void computeItemTotalAttribute();
	//장착중인 무기 반환
	Item* getEquipWeapon();

	CPlayer_Attribute getItemTotalAttribute(){return _totalAttribute;}
	void setEquipWeapon(Item* witem)
	{
		if (_equipWeapon == nullptr) _equipWeapon = witem;
		else if (_equipWeapon != nullptr) _equipWeapon = nullptr;
		computeItemTotalAttribute();
	}
	void setEquipArmor(Item* aitem)
	{
		if (_equipArmor == nullptr) _equipArmor = aitem;
		else if (_equipArmor != nullptr) _equipArmor = nullptr;
		computeItemTotalAttribute();
	}
	void setEquipShoes(Item* sitem)
	{
		if (_equipShoes == nullptr) _equipShoes = sitem;
		else if (_equipShoes != nullptr) _equipShoes = nullptr;
		computeItemTotalAttribute();
	}
	void setEquipHat(Item* hitem)
	{
		if(_equipHat==nullptr) _equipHat = hitem;
		else if (_equipHat != nullptr) _equipHat = nullptr;
		computeItemTotalAttribute();
	}

	void checkMouse(void);

	bool getIsShowInven(void) { return _isShowInven; }
	void setIsShowInven(bool isShowInven) { _isShowInven = isShowInven; }

};


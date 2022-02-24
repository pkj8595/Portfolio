#pragma once
#include "GameNode.h"
#include "mButton.h"
#include "ItemManager.h"

#define	ABILITY_IMG_OFFSET		50
#define	ABILITY_IMG_X			300
#define	ABILITY_IMG_Y			(WINSIZE_Y-100)

#define	INVENTORY_IMG_OFFSETX		40
#define	INVENTORY_IMG_OFFSETY		40
#define	INVENTORY_IMG_X				150
#define	INVENTORY_IMG_Y				150

class Inventory : public GameNode
{
	typedef struct STInvenPos
	{
		my::Image* img;
		POINT pt;
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

	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;

	Item* _equipWeapon;
	Item* _equipArmor;
	Item* _equipShoes;
	Item* _emptyItem;

	//총 아이템 능력치
	CPlayer_Attribute _totalAttribute;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renderInventoryBase();

	CPlayer_Attribute getItemTotalAttribute(){return _totalAttribute;}
	//장착중인 무기 반환
	Item* getEquipWeapon();

	void setEquipWeapon(Item* witem)
	{
		_equipWeapon = witem; 
		computeItemTotalAttribute();
	}
	void setEquipArmor(Item* aitem)
	{
		_equipArmor = aitem; 
		computeItemTotalAttribute();
	}
	void setEquipShoes(Item* sitem)
	{
		_equipShoes = sitem; 
		computeItemTotalAttribute();
	}

	//총 아이템 능력치 합산
	void computeItemTotalAttribute();
	//인벤토리 아이템 추가
	void pushItem(Item* item);

	void showInventoryItem();
	void showAbilityItem();
	

};


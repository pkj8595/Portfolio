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

	Item* _equipWeapon;		//�������� ����
	Item* _equipArmor;		//�������� �Ƹ�
	Item* _equipShoes;		//�������� �Ź�
	Item* _equipHat;		//�������� �Ź�
	Item* _emptyItem;		//�� ������

	CPlayer_Attribute _totalAttribute;	//�� ������ �ɷ�ġ

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
	//�κ��丮 ������ �߰�
	void pushItem(Item* item);
	//�� ������ �ɷ�ġ �ջ�
	void computeItemTotalAttribute();
	//�������� ���� ��ȯ
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


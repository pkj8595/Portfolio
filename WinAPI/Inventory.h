#pragma once
#include "GameNode.h"
#include "ItemManager.h"

#define	ABILITY_IMG_OFFSET		50
#define	ABILITY_IMG_X			300
#define	ABILITY_IMG_Y			(WINSIZE_Y-50)

#define	INVENTORY_IMG_OFFSETX		40
#define	INVENTORY_IMG_OFFSETY		40

#define PUSH_ITEM_MESSEGE		0.8f

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
		STInvenPosBtn()
		{
			frameX = 0;
		}
	}InvenPosBtn;

	typedef struct STItemInfoWindow
	{
		my::Image* img;
		RECT rc;
	}InfoWindow;

	typedef struct STItemInfoText
	{
		string str;
		COLORREF color;
		int fontSize;
		POINT pt;

		STItemInfoText()
		{
			str = "";
			color = RGB(255, 255, 255);
			fontSize = 20;
			pt = POINT{0,0};
		}
	}InfoWindowText;

	ItemManager* _itemManager;
	my::Image* _inventoryBackground;
	RECT _rc;
	int _x, _y;
	//InvenPos _combineBackground;
	//InvenPos _inventoryHintCorner;
	//InvenPos _inventoryClickHelp;
	//InvenPosBtn _combineBtnIcon2;
	InvenPos _inventoryGoldIcon;
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

	InfoWindow _itemInfoWindow;
	float _worldTime;
	bool _isShowGetItem;
	int _showGetItemImgNum;

	bool _isExcuteEnchant;
	bool _isEnchantSuccess;
	float _enchantSuccessWorldTime;
	string _enchantStr;

	//todo
	int _gold;
	RECT _goldRc;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void renderInventoryBase(void);
	void showInventoryItem(void);
	void showAbilityItem(void);

	void checkMouseEvent(void);
	void computeRect(void);

	void renderInvenAttributeText(void);
	void equipRender(void);
	void renderItemInfoWindow();
	void removeItem(Item* item);//인벤토리 아이템 없앨때 사용

	bool getIsShowInven(void) { return _isShowInven; }
	void setIsShowInven(bool isShowInven) { _isShowInven = isShowInven; }
	void setPTotalattribute(CPlayer_Attribute* att)
	{
		_ptotalAttribute = att;
	}
	void setPlayerAttribute(CPlayer_Attribute* att)
	{
		_pAttribute = att;
	}

	int getGold() { return _gold; }
	void setGold(int gold) { _gold = gold; }

	string changeItemTypeToStr(EITEM_TYPE type);
	string changeAttributeToStr(CPlayer_Attribute attri);

	void decreaseDurability(int dufault = 8);
	void repairWeapon(int gold);

	//==========================
	// ### Player Equipment ###
	//==========================
	//인벤토리 아이템 추가
	bool buyItem(int num);
	void pushItem(Item* item);
	void pushItem(int num);
	inline void updatePushItemMassege(Item* item);
	void renderPushItemMassege();

	void inventorydrawText(std::string &str, const RECT &massgeRc,int fontsize, COLORREF color,bool isCenter);

	//총 아이템 능력치 합산
	void computeItemTotalAttribute();
	//장착중인 무기 반환
	Item** getEquipWeapon() { return &_equipWeapon; };

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

	
};


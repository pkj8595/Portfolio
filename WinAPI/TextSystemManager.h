#pragma once
#include "GameNode.h"
#include "ItemClass.h"
#define TEXT_MAX 10

struct TagText
{
	LPCWSTR name;
	LPCWSTR script;
};

class TextSystemManager :public GameNode
{
private:

	TagText _text[TEXT_MAX];
	const int SCRIPT_MAX_LENGTH = 55;
	string _itemName;
	string _iteminfo;
	int _price;

	string _shopNameText;
	string _shopPriceText;

	int _eventArrText;
	int _anvilArrText;
	int _textBufferCnt;
	int _textindex;

	float _textAlpha;
	float _selectOneAlpha;
	float _selectTwoAlpha;
	float _selectThreeAlpha;

	RECT _chatRc;			// ÆË¾÷ Ã¢ rc
	RECT _chatWriteRc;
	RECT _boxChatRc;
	RECT _nameRc;
	RECT _anvilNameRc;
	
	RECT _shopsel_OneRc;
	RECT _shopsel_TwoRc;
	
	RECT _select_oneRc;
	RECT _select_TwoRc;
	RECT _select_ThrRc;
	
	RECT _anvilsel_oneRc;
	RECT _anvilsel_TwoRc;

	my::Image* _chatImage;
	my::Image* _BoxchatImage;
	my::Image* _nameImage;
	my::Image* _selImage;
	my::Image* _anvilnameImage;

	char temp[32];
	vector<string> weapon_Selectdata;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void ShopLog(string itemName, int price);
	void EventLog(int arrText);
	void AnvilLog(int arrText);

	void setShopdata(string itemName, int price);

	bool isShopOpen;
	bool isEventOpen;
	bool isAnvilOpen;

	bool isEventText;
	bool isShowText;
	bool iscollBox;

	bool isShopCol;
	bool isAnvilCol;

	bool isWeaponSword;
	bool isWeaponBow;
	bool isWeaponEmpty;

	bool isShopbuy;
	bool isrepairbuy;

	TextSystemManager() {}
	~TextSystemManager() {}
};

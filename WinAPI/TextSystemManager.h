#pragma once
#include "GameNode.h"
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
	string _text1;
	string _text2;
	int _price;
	int _eventArrText;
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
	RECT _shopsel_OneRc;
	RECT _shopsel_TwoRc;
	RECT _select_oneRc;
	RECT _select_TwoRc;
	RECT _select_ThrRc;
	


	my::Image* _chatImage;
	my::Image* _BoxchatImage;
	my::Image* _nameImage;
	my::Image* _selImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void ShopLog(string itemName, string iteminfo, int price);
	void ShopLog(string itemName, int price);
	void EventLog(int arrText);

	bool isEventText;
	bool isShowText;
	bool iscollBox;
	bool isShopcol;
	bool isWeaponSword;
	bool isWeaponBow;
	bool isWeaponEmpty;
	bool isShopbuy;

	TextSystemManager() {}
	~TextSystemManager() {}
};

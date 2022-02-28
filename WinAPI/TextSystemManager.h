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
	wstring _itemName;
	wstring _iteminfo;
	wstring _price;
	int _eventArrText;
	int _textBufferCnt;
	int _textindex;
	float _textAlpha;
	float _selectOneAlpha;
	float _selectTwoAlpha;
	float _selectThreeAlpha;

	

	RECT _chatRc;			// 팝업 창 rc
	RECT _boxChatRc;
	RECT _nameRc;
	RECT _select_oneRc;
	RECT _select_TwoRc;
	RECT _select_ThrRc;

	LPCWSTR Shop_talk[2];	//wstring -> LPCWSTR로 변환할 변수
	my::Image* _chatImage;
	my::Image* _BoxchatImage;
	my::Image* _nameImage;
	my::Image* _selImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void ShopLog(wstring itemName, wstring iteminfo, wstring price);
	void EventLog(int arrText);

	bool iscollText;
	bool iscollBox;
	bool isWeaponSword;
	bool isWeaponBow;
	bool isWeaponEmpty;

	TextSystemManager() {}
	~TextSystemManager() {}
};

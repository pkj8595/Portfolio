#pragma once
#include "GameNode.h"
#define TEXT_MAX 500

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
	wstring _price;
	int _eventArrText;
	int _textBufferCnt;
	int _textAlpha;
	int _count;

	RECT _chatRc;			// �˾� â rc
	RECT _nameRc;
	RECT _select_oneRc;
	RECT _select_TwoRc;

	LPCWSTR Shop_talk;	//wstring -> LPCWSTR�� ��ȯ�� ����
	my::Image* _chatImage;
	my::Image* _nameImage;
	my::Image* _selImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void shopLog(wstring itemName, wstring price);
	void EventLog(int arrText);

	bool test;

	TextSystemManager() {}
	~TextSystemManager() {}
};

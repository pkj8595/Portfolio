#pragma once
#include "GameNode.h"
#define TEXT_MAX 500

struct TagText
{
	LPCWSTR name;
	LPCWSTR script;
};

struct TagText2
{
	LPCWSTR script;
	LPCWSTR name;
	LPCWSTR price;
	LPCWSTR script2;
};

class TextSystemManager :public GameNode
{
private:
	TagText _text[TEXT_MAX];
	TagText2 _text2[2];
	const int SCRIPT_MAX_LENGTH = 55;
	LPCWSTR _itemName;
	LPCWSTR _price;
	int _eventArrText;
	int _chatArrText;
	int _textBufferCnt;
	int _textAlpha;
	int _count;

	RECT _chatRc;			// �˾� â rc
	RECT _nameRc;
	LPCWSTR _script;	// ���� �޾ƿ� ���ڰ�
	my::Image* _Chatimage;
	my::Image* _Nameimage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void shopLog(int arrText, LPCWSTR itemName, LPCWSTR price);
	void EventLog(int arrText);

	TextSystemManager() {}
	~TextSystemManager() {}
};

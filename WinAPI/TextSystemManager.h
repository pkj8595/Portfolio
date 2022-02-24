#pragma once
#include "GameNode.h"
#define TEXT_MAX 500

struct Text
{
	LPCWSTR name;
	LPCWSTR script;
};

class TextSystemManager :public GameNode
{
private:
	Text _text[TEXT_MAX];
	const int SCRIPT_MAX_LENGTH = 55;
	LPCWSTR _itemName;
	LPCWSTR _price;
	int _arrtext;
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
	void shopLog(LPCWSTR itemName, LPCWSTR price);
	void EventLog(int arrText);

	TextSystemManager() {}
	~TextSystemManager() {}
};

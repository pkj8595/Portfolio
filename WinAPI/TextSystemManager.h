#pragma once
#include "GameNode.h"

#define TEXT_NUM 1000

struct Text
{
	LPCWSTR name;
	LPCWSTR script;
};

class TextSystemManager :public GameNode
{
private:
	struct Text _text[TEXT_NUM];
	const int SCRIPT_MAX_LENGTH = 55;
	string _name;
	int _price;
	int _textIndex;
	int _textBufferCnt;
	int _textAlpha;
	int _count;

	RECT _chatRc;			// 팝업 창 rc
	RECT _nameRc;
	LPCWSTR _script;	// 값을 받아올 글자값
	my::Image* _Chatimage;
	my::Image* _Nameimage;

public:
	HRESULT init(void);
	void release(void);
	void update(int arrNum);
	void render(int arrNum);

	TextSystemManager() {}
	~TextSystemManager() {}
};
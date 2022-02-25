#pragma once
#include "Stdafx.h"
#include "TextSystemManager.h"

HRESULT TextSystemManager::init(void)
{
	_chatImage = IMAGEMANAGER->addImage("Talkbox","Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 850, 200, true, RGB(255, 0, 255));
	_nameImage = IMAGEMANAGER->addImage("Namebox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 125, 65, true, RGB(255, 0, 255));
	_selImage = IMAGEMANAGER->addImage("SelOne", "Resource/Images/Lucie/CompleteImg/UI/SelectBox.bmp", 120, 50, true, RGB(255, 0, 255));

	_textBufferCnt = 0;
	_count = 0;
	_eventArrText = 0;

	iscollText = false;

	_text[0] = { L"", L"기본 무기 중 하나를 가져갈 수 있다. 어떤 종류를 가져갈까?" };
	_text[1] = { L"", L"아무 것도 안 들어있겠지?" };
	_text[2] = { L"", L"거울같이 생겼는데, 불투명해" };
	_text[3] = { L"", L"...지금은 보고 싶지 않아." };
	_text[4] = { L"", L"잠겨있어." };
	

	_chatRc = RectMake(WINSIZE_X*0.08, WINSIZE_Y*0.75, _chatImage->getWidth(), _chatImage->getHeight());
	_nameRc = RectMake(WINSIZE_X*0.06, WINSIZE_Y*0.68, _nameImage->getWidth(), _nameImage->getHeight());
	_select_oneRc = RectMake(WINSIZE_X*0.12, WINSIZE_Y*0.1, _selImage->getWidth(), _selImage->getHeight());
	_select_TwoRc = RectMake(WINSIZE_X*0.12, WINSIZE_Y*0.85, _selImage->getWidth(), _selImage->getHeight());

	
	return S_OK;
}

void TextSystemManager::release(void)
{
	//! Do Nothing
}

void TextSystemManager::update(void)
{
	
	if (iscollText) _textBufferCnt += 1; _textAlpha += 4.0f;
	if (!iscollText) _textBufferCnt = 0;

	if (_textAlpha >= 230) _textAlpha = 230;
}

void TextSystemManager::render(void)
{
	shopLog(_itemName, _price);
	EventLog(_eventArrText);
}

void TextSystemManager::shopLog(wstring itemName, wstring price)
{
	_itemName = itemName;
	_price = price;
	
	wstring text = L"그건 " + _itemName + L". " + _price + L"골드야. 살래?";
	
	Shop_talk = text.c_str();

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	IMAGEMANAGER->alphaRender("Namebox", getMemDC(), _nameRc.left, _nameRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "야놀자 야체", 27, 15,
		L"마리", wcslen(L"마리"), RGB(0, 0, 255));

	IMAGEMANAGER->render("SelOne", getMemDC(), _select_oneRc.left, _select_oneRc.top);
	IMAGEMANAGER->render("SelOne", getMemDC(), _select_TwoRc.left, _select_TwoRc.top);

	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.14, WINSIZE_Y*0.78, "야놀자 야체", 27, 15,
		Shop_talk, ((_textBufferCnt / 4) > wcslen(Shop_talk) ? wcslen(Shop_talk) : (_textBufferCnt / 4)), RGB(255, 255, 255));

}

void TextSystemManager::EventLog(int arrText)
{
	_eventArrText = arrText;

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "야놀자 야체", 27, 15,
		_text[arrText].name, wcslen(_text[arrText].name), RGB(0, 0, 255));

	

	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.78, "야놀자 야체", 27, 15, _text[arrText].script, 
		((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 0, 255));
}
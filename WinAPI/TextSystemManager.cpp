#pragma once
#include "Stdafx.h"
#include "TextSystemManager.h"

HRESULT TextSystemManager::init(void)
{
	_Chatimage = IMAGEMANAGER->addImage("Talkbox","Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 850, 200, true, RGB(255, 0, 255));
	_Nameimage = IMAGEMANAGER->addImage("Namebox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 125, 65, true, RGB(255, 0, 255));

	_textBufferCnt = 0;
	_count = 0;
	int _eventArrText = 0;
	int _chatArrText = 0;

	_text[0] = { L"", L"±âº» ¹«±â Áß ÇÏ³ª¸¦ °¡Á®°¥ ¼ö ÀÖ´Ù. ¾î´À°É °¡Á®°¥±î?" };
	_text[1] = { L"", L"¿ÊÀå" };
	_text[2] = { L"", L"°Å¿ï" };

	_text2[0] = { L"ÀÌ°Ç", _itemName, _price, L"°ñµå¾ß." };
	_text2[1] = { L"»ì·¡?" };

	_chatRc = RectMake(WINSIZE_X*0.08, WINSIZE_Y*0.75, _Chatimage->getWidth(), _Chatimage->getHeight());
	_nameRc = RectMake(WINSIZE_X*0.06, WINSIZE_Y*0.68, _Nameimage->getWidth(), _Nameimage->getHeight());
	return S_OK;
}

void TextSystemManager::release(void)
{
	//! Do Notting
}

void TextSystemManager::update(void)
{
	_textAlpha += 4.0f;
	
	_textBufferCnt += 1;

	if (_textAlpha >= 230) _textAlpha = 230;
}

void TextSystemManager::render(void)
{
	shopLog(_chatArrText, _itemName, _price);
	EventLog(_eventArrText);
}

void TextSystemManager::shopLog(int arrText, LPCWSTR itemName, LPCWSTR price)
{
	_itemName = itemName;
	_price = price;
	_chatArrText = arrText;

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	IMAGEMANAGER->alphaRender("Namebox", getMemDC(), _nameRc.left, _nameRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "¸¼Àº °íµñ", 27, 15,
		L"¸¶¸®", wcslen(L"¸¶¸®"), RGB(0, 0, 255));

	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.78, "¸¼Àº °íµñ", 27, 15,
		_text2[arrText].script, ((_textBufferCnt / 4) > wcslen(_text2[arrText].script) ? wcslen(_text2[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));
}

void TextSystemManager::EventLog(int arrText)
{
	_eventArrText = arrText;

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "¸¼Àº °íµñ", 27, 15,
		_text[arrText].name, wcslen(_text[arrText].name), RGB(0, 0, 255));

	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.78, "¸¼Àº °íµñ", 27, 15, _text[arrText].script, 
		((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 0, 255));
}

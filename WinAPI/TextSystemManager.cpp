#pragma once
#include "Stdafx.h"
#include "TextSystemManager.h"

HRESULT TextSystemManager::init(void)
{
	_chatImage = IMAGEMANAGER->addImage("Talkbox","Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 850, 200, true, RGB(255, 0, 255));
	_BoxchatImage = IMAGEMANAGER->addImage("WP_BoxTextBox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 850, 250, true, RGB(255, 0, 255));
	_nameImage = IMAGEMANAGER->addImage("Namebox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 125, 65, true, RGB(255, 0, 255));
	_selImage = IMAGEMANAGER->addImage("SelOne", "Resource/Images/Lucie/CompleteImg/UI/SelectBox.bmp", 180, 50, true, RGB(255, 0, 255));

	_textBufferCnt = 0;
	_textindex = 0;
	_eventArrText = 0;

	iscollText = false;
	iscollBox = false;

	_text[0] = { L"", L"기본 무기 중 하나를 가져갈 수 있다. 어떤 종류를 가져갈까?" };
	_text[1] = { L"", L"아무 것도 안 들어있겠지?" };
	_text[2] = { L"", L"거울같이 생겼는데, 불투명해." };
	_text[3] = { L"", L"...지금은 보고 싶지 않아." };
	_text[4] = { L"", L"잠겨있어." };
	

	_chatRc = RectMake(WINSIZE_X*0.08, WINSIZE_Y*0.75, _chatImage->getWidth(), _chatImage->getHeight());
	_boxChatRc = RectMake(WINSIZE_X*0.08, WINSIZE_Y*0.72, _chatImage->getWidth(), _chatImage->getHeight());
	_nameRc = RectMake(WINSIZE_X*0.06, WINSIZE_Y*0.68, _nameImage->getWidth(), _nameImage->getHeight());
	_select_oneRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.79, _selImage->getWidth(), _selImage->getHeight());
	_select_TwoRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.84, _selImage->getWidth(), _selImage->getHeight());
	_select_ThrRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.89, _selImage->getWidth(), _selImage->getHeight());

	
	return S_OK;
}

void TextSystemManager::release(void)
{
	//! Do Nothing
}

void TextSystemManager::update(void)
{
	
	if (iscollText) { _textBufferCnt += 1; _textAlpha += 4.0f; }
	if (!iscollText) { _textBufferCnt = 0; }
	if (_textAlpha >= 230.0f) { _textAlpha = 230.0f; }

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

	}

	if (iscollBox)
	{
		if (PtInRect(&_select_oneRc, _ptMouse))
		{
			_selectOneAlpha = 230.0f;
			isWeaponSword = true;
		}
		else _selectOneAlpha = 0.0f;

		if (PtInRect(&_select_TwoRc, _ptMouse))
		{
			_selectTwoAlpha = 230.0f;
			isWeaponBow = true;
		}
		else _selectTwoAlpha = 0.0f;
		
		if (PtInRect(&_select_ThrRc, _ptMouse))
		{
			_selectThreeAlpha = 230.0f;
			isWeaponEmpty = true;
		}
		else _selectThreeAlpha = 0.0f;
	}
}

void TextSystemManager::render(void)
{
	ShopLog(_itemName, _iteminfo, _price);
	EventLog(_eventArrText);
}

void TextSystemManager::ShopLog(wstring itemName, wstring iteminfo, wstring price)
{

	_itemName = itemName;
	_iteminfo = iteminfo;
	_price = price;

	wstring text = L"그건 " + _itemName + L". " + _iteminfo + L".";
	wstring text2 = L"가격은 " + _price + L" 골드인데, 살래?";
	
	Shop_talk[0] = text.c_str();
	Shop_talk[1] = text2.c_str();

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	IMAGEMANAGER->alphaRender("Namebox", getMemDC(), _nameRc.left, _nameRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "둥근모꼴", 27, 15,
		L"마리", wcslen(L"마리"), RGB(0, 0, 255));

	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "둥근모꼴", 27, 15,
		L"응.", wcslen(L"응."), RGB(0, 0, 255));
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "둥근모꼴", 27, 15,
		L"아니.", wcslen(L"아니."), RGB(0, 0, 255));
	IMAGEMANAGER->render("SelOne", getMemDC(), _select_oneRc.left, _select_oneRc.top);
	IMAGEMANAGER->render("SelOne", getMemDC(), _select_TwoRc.left, _select_TwoRc.top);

	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.14, WINSIZE_Y*0.78, "둥근모꼴", 27, 15,
		Shop_talk[_textindex], ((_textBufferCnt / 4) > wcslen(Shop_talk[_textindex]) ? wcslen(Shop_talk[_textindex]) : (_textBufferCnt / 4)), RGB(255, 255, 255));

}

void TextSystemManager::EventLog(int arrText)
{
	_eventArrText = arrText;
	if (!iscollBox) 
	{
		IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "둥근모꼴", 27, 15,
			_text[arrText].name, wcslen(_text[arrText].name), RGB(0, 0, 255));

		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.78, "둥근모꼴", 27, 15, _text[arrText].script,
			((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));
	}

	if (iscollBox)
	{
		IMAGEMANAGER->alphaRender("WP_BoxTextBox", getMemDC(), _boxChatRc.left, _boxChatRc.top, _textAlpha);
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "둥근모꼴", 27, 15,
			_text[arrText].name, wcslen(_text[arrText].name), RGB(0, 0, 255));

		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.75, "둥근모꼴", 27, 15, _text[arrText].script,
			((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));

		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_oneRc.left, _select_oneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_TwoRc.left, _select_TwoRc.top, _selectTwoAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_ThrRc.left, _select_ThrRc.top, _selectThreeAlpha);
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.80, "둥근모꼴", 27, 15,
			L"검", wcslen(L"검"), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.85, "둥근모꼴", 27, 15,
			L"활", wcslen(L"활"), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.90, "둥근모꼴", 27, 15,
			L"안 가져갈래!", wcslen(L"안 가져갈래!"), RGB(255, 255, 255));
		
	}
}
#pragma once
#include "Stdafx.h"
#include "TextSystemManager.h"
#include "Player.h"
#include "LobbyPlayer.h"


HRESULT TextSystemManager::init(void)
{
	_chatImage = IMAGEMANAGER->addImage("Talkbox","Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 700, 170, true, RGB(255, 0, 255));
	_BoxchatImage = IMAGEMANAGER->addImage("WP_BoxTextBox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 800, 170, true, RGB(255, 0, 255));
	_nameImage = IMAGEMANAGER->addImage("Namebox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 125, 45, true, RGB(255, 0, 255));
	_anvilnameImage = IMAGEMANAGER->addImage("AnvilNamebox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 200, 45, true, RGB(255, 0, 255));
	_selImage = IMAGEMANAGER->addImage("SelOne", "Resource/Images/Lucie/CompleteImg/UI/SelectBox.bmp", 130, 30, true, RGB(255, 0, 255));

	_textBufferCnt = 0;
	_textindex = 0;
	_eventArrText = 0;

	isShowText = false;
	iscollBox = false;
	isShopOpen = false;
	isShopbuy = false;

	_shopNameText = "";
	_shopPriceText = "";

	_text[0] = { L"", L"기본 무기 중 하나를 가져갈 수 있다. 어떤 종류를 가져갈까?" };
	_text[1] = { L"", L"아무 것도 안 들어있겠지?" };
	_text[2] = { L"", L"거울같이 생겼는데, 불투명해." };
	_text[3] = { L"", L"...지금은 보고 싶지 않아." };
	_text[4] = { L"", L"잠겨있어." };
	_text[5] = { L"", L"지금 그 무기를 수리할텐가?" };
	_text[6] = { L"", L"자, 수리가 완료되었네." };

	_textPosition = PointMake(1000, 550);
	
	_chatRc = RectMake(_textPosition.x*0.13, _textPosition.y*0.66, _chatImage->getWidth(), _chatImage->getHeight());
	_chatWriteRc = RectMake(_textPosition.x*0.14, _textPosition.y*0.68, _chatImage->getWidth(), _chatImage->getHeight());
	_boxChatRc = RectMake(_textPosition.x*0.08, _textPosition.y*0.66, _chatImage->getWidth(), _chatImage->getHeight());
	_nameRc = RectMake(_textPosition.x*0.13, _textPosition.y*0.58, _nameImage->getWidth(), _nameImage->getHeight());
	_anvilNameRc = RectMake(_textPosition.x*0.13, _textPosition.y*0.58, _anvilnameImage->getWidth(), _anvilnameImage->getHeight());

	_shopsel_OneRc = RectMake(_textPosition.x*0.14, _textPosition.y*0.80, _selImage->getWidth(), _selImage->getHeight());
	_shopsel_TwoRc = RectMake(_textPosition.x*0.14, _textPosition.y*0.86, _selImage->getWidth(), _selImage->getHeight());
	_select_oneRc = RectMake(_textPosition.x*0.1, _textPosition.y*0.76, _selImage->getWidth(), _selImage->getHeight());
	_select_TwoRc = RectMake(_textPosition.x*0.1, _textPosition.y*0.82, _selImage->getWidth(), _selImage->getHeight());
	_select_ThrRc = RectMake(_textPosition.x*0.1, _textPosition.y*0.88, _selImage->getWidth(), _selImage->getHeight());
	_anvilsel_oneRc = RectMake(_textPosition.x*0.14, _textPosition.y*0.80, _selImage->getWidth(), _selImage->getHeight());
	_anvilsel_TwoRc = RectMake(_textPosition.x*0.14, _textPosition.y*0.86, _selImage->getWidth(), _selImage->getHeight());

	return S_OK;
}

void TextSystemManager::release(void)
{
	//! Do Nothing
}

void TextSystemManager::update(void)
{
	//isShowText가 true가 되었을때 BufferCnt 및 _textAlpha 값 더하기
	if (isShowText)
	{ 
		_textBufferCnt += 1;
		_textAlpha += 4.0f; 
	}
	//isShowText가 false가 되었을때 BufferCnt 및 _textAlpha 값 0으로 초기화
	else if (!isShowText)
	{
		_textBufferCnt = 0; 
		_textindex = 0;
	}
	//_textAlpha가 230 이상을 초과하면 230으로 고정해두기.
	if (_textAlpha >= 230.0f) { _textAlpha = 230.0f; }
	
	
	// 엔터를 눌렀을 경우
	if (KEYMANAGER->isOnceKeyDown('Z') && isShowText)
	{
		// _textBufferCnt과 _text1.size()를 비교했을 때 _text1.size()가 더 크다면
		if (_textBufferCnt < _shopNameText.size())
		{
			// bufferCnt은 _text1.size의 값과 같은 값을 가지게 된다.
			_textBufferCnt = _shopNameText.size();
		}
		// 저 조건에 충족하지 않는다면 _textindex를 1로 고정하고 버튼 렌더에 필요한 isShopcol을 호출한다.
		else
		{
			if (isShopOpen)
			{
				_textindex = 1;
				isShopCol = true;
			}

			if (isAnvilOpen)
			{
				isShowText = false;
				isAnvilOpen = false;
				isrepairbuy = false;
			}
		}
	}

	// 버튼 렉트 박스에 충돌했을 경우 알파값을 230.0f로 고정, 아닐 경우 0으로 초기화
	if (iscollBox)
	{
		if (PtInRect(&_select_oneRc, _ptMouse))
		{
			_selectOneAlpha = 230.0f;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/ui_ok.wav");
				weapon_Selectdata.clear();
				weapon_Selectdata.push_back(_itoa(20, temp, 10));
				TEXTDATAMANAGER->save("로비 무기 선택.text", weapon_Selectdata);
				isShowText = false;
				iscollBox = false;
			}
		}
		else 
		{ 
			_selectOneAlpha = 0.0f; 
		}

		if (PtInRect(&_select_TwoRc, _ptMouse))
		{
			_selectTwoAlpha = 230.0f;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/ui_ok.wav");
				weapon_Selectdata.clear();
				weapon_Selectdata.push_back(_itoa(23, temp, 10));
				TEXTDATAMANAGER->save("로비 무기 선택.text", weapon_Selectdata);
				isShowText = false;
				iscollBox = false;
			}
		}
		else
		{
			_selectTwoAlpha = 0.0f;
		}
		
		if (PtInRect(&_select_ThrRc, _ptMouse))
		{
			_selectThreeAlpha = 230.0f;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/ui_ok.wav");
				weapon_Selectdata.clear();
				TEXTDATAMANAGER->save("로비 무기 선택.text", weapon_Selectdata);
				isShowText = false;
				iscollBox = false;
			}
		}
		else
		{
			_selectThreeAlpha = 0.0f;
		}
	}

	//isShopcol이 true가 되면
	if (isShopCol)
	{
	// 상점 버튼 렉트 박스에 닿으면 알파값을 230.0f로 고정하고
		if (PtInRect(&_shopsel_OneRc, _ptMouse))
		{
			_selectOneAlpha = 230.0f;
			// 좌클릭할 경우 구매 버튼이 true된 후 isShopOpen과 isShowText가 false된다.
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				isShopbuy = true;
				isShopCol = false;
				isShopOpen = false;
				isShowText = false;
			}
		}
		else
		{
			_selectOneAlpha = 0.0f;
		}
		
		// 상점 버튼 렉트 박스에 닿으면 알파값을 230.0f로 고정하고
		if (PtInRect(&_shopsel_TwoRc, _ptMouse))
		{
			_selectTwoAlpha = 230.0f;
			// 좌클릭할 경우 3개의 변수가 false가 된다.
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/ui_ok.wav");
				isShowText = false;
				isShopCol = false;
				isShopOpen = false;
			}
		}
		else
		{
			_selectTwoAlpha = 0.0f;
		}
	}

	if (isAnvilCol)
	{
		if (PtInRect(&_anvilsel_oneRc, _ptMouse))
		{
			_selectOneAlpha = 230.0f;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/ui_ok.wav");
				isrepairbuy = true;
				isShowText = true;
			}
		}
		else
		{
			_selectOneAlpha = 0.0f;
		}

		if (PtInRect(&_anvilsel_TwoRc, _ptMouse))
		{
			_selectTwoAlpha = 230.0f;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/ui_ok.wav");
				isAnvilCol = false;
				isShowText = false;
				isAnvilOpen = false;
			}
		}
		else
		{
			_selectTwoAlpha = 0.0f;
		}
	}
}

void TextSystemManager::render(void)
{
	if (isShopOpen) 
	{ 
		ShopLog(_itemName, _price); 
	}

	if (isEventOpen)
	{
		EventLog(_eventArrText);
	}

	if (isAnvilOpen)
	{
		AnvilLog(_anvilArrText);
	}
}

void TextSystemManager::setShopdata(string itemName, int price)
{
	_itemName = itemName;
	_price = price;

	_shopNameText = "그건 " + _itemName + ". ";
	_shopPriceText = "가격은 " + to_string(_price) + "골드인데, 살래?";
}

void TextSystemManager::ShopLog(string itemName, int price)
{
	char* shop_talk1 = new char[_shopNameText .size() + 1];
	copy(_shopNameText.begin(), _shopNameText.end(), shop_talk1);
	shop_talk1[_shopNameText.size()] = '\0';

	char* shop_talk2 = new char[_shopPriceText.size() + 1];
	copy(_shopPriceText.begin(), _shopPriceText.end(), shop_talk2);
	shop_talk2[_shopPriceText.size()] = '\0';

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);																																				
	IMAGEMANAGER->alphaRender("Namebox", getMemDC(), _nameRc.left, _nameRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.165, _textPosition.y*0.6, "둥근모꼴", 25, 15,
		L"마리", wcslen(L"마리"), RGB(255, 255, 255));

	// _textindex가 0일때 _chatWriteRc에서부터 문구 출력
	if (_textindex == 0)
	{
		FONTMANAGER->drawText(getMemDC(), _chatWriteRc, "둥근모꼴", 22, 15, shop_talk1, ((_textBufferCnt) > strlen(shop_talk1) ? strlen(shop_talk1) : (_textBufferCnt)), RGB(255, 255, 255));
	}
	// _textindex가 1일때 _chatWriteRc에서부터 문구 출력
	else if (_textindex == 1)
	{
		FONTMANAGER->drawText(getMemDC(), _chatWriteRc, "둥근모꼴", 22, 15, shop_talk2, ((_textBufferCnt) > strlen(shop_talk2) ? strlen(shop_talk2) : (_textBufferCnt)), RGB(255, 255, 255));
	}

	// isShopcol이 true일때 선택 박스 및 선택 박스 안에 들어갈 텍스트 출력
	if (isShopCol)
	{
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _shopsel_OneRc.left, _shopsel_OneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _shopsel_TwoRc.left, _shopsel_TwoRc.top, _selectTwoAlpha);
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.80, "둥근모꼴", 22, 15,
			L"응.", wcslen(L"응."), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.86, "둥근모꼴", 22, 15,
			L"아니.", wcslen(L"아니."), RGB(255, 255, 255));
	}
	
	// shop_talk 1,2 삭제
	delete[] shop_talk1;
	delete[] shop_talk2;
}

void TextSystemManager::EventLog(int arrText)
{
	_eventArrText = arrText;
	if (!iscollBox) 
	{
		IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.13, _textPosition.y*0.62, "둥근모꼴", 22, 15,
			_text[arrText].name, wcslen(_text[arrText].name), RGB(255, 255, 255));

		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.14, _textPosition.y*0.69, "둥근모꼴", 22, 15, _text[arrText].script,
			((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));
	}

	if (iscollBox)
	{
		IMAGEMANAGER->alphaRender("WP_BoxTextBox", getMemDC(), _boxChatRc.left, _boxChatRc.top, _textAlpha);

		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.1, _textPosition.y*0.69, "둥근모꼴", 22, 15, _text[arrText].script,
			((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));

		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_oneRc.left, _select_oneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_TwoRc.left, _select_TwoRc.top, _selectTwoAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_ThrRc.left, _select_ThrRc.top, _selectThreeAlpha);
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.1, _textPosition.y*0.77, "둥근모꼴", 22, 15,
			L"검", wcslen(L"검"), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.1, _textPosition.y*0.83, "둥근모꼴", 22, 15,
			L"활", wcslen(L"활"), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.1, _textPosition.y*0.89, "둥근모꼴", 22, 15,
			L"안 가져갈래!", wcslen(L"안 가져갈래!"), RGB(255, 255, 255));
		
	}
}

void TextSystemManager::AnvilLog(int arrText)
{
	_anvilArrText = arrText;

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	IMAGEMANAGER->alphaRender("AnvilNamebox", getMemDC(), _anvilNameRc.left, _anvilNameRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.59, "둥근모꼴", 22, 15,
		L"말하는 모루할배", wcslen(L"말하는 모루할배"), RGB(0, 0, 255));

	FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.14, _textPosition.y*0.69, "둥근모꼴", 22, 15, _text[arrText].script,
		((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));

	if (isAnvilCol)
	{
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _anvilsel_oneRc.left, _anvilsel_oneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _anvilsel_TwoRc.left, _anvilsel_TwoRc.top, _selectTwoAlpha);
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.81, "둥근모꼴", 22, 15,
			L"수리한다.", wcslen(L"수리한다."), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.87, "둥근모꼴", 22, 15,
			L"무시한다.", wcslen(L"무시한다."), RGB(255, 255, 255));
	}
}


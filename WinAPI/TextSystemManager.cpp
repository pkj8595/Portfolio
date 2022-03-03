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

	_text[0] = { L"", L"�⺻ ���� �� �ϳ��� ������ �� �ִ�. � ������ ��������?" };
	_text[1] = { L"", L"�ƹ� �͵� �� ����ְ���?" };
	_text[2] = { L"", L"�ſﰰ�� ����µ�, ��������." };
	_text[3] = { L"", L"...������ ���� ���� �ʾ�." };
	_text[4] = { L"", L"����־�." };
	_text[5] = { L"", L"���� �� ���⸦ �������ٰ�?" };
	_text[6] = { L"", L"��, ������ �Ϸ�Ǿ���." };

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
	//isShowText�� true�� �Ǿ����� BufferCnt �� _textAlpha �� ���ϱ�
	if (isShowText)
	{ 
		_textBufferCnt += 1;
		_textAlpha += 4.0f; 
	}
	//isShowText�� false�� �Ǿ����� BufferCnt �� _textAlpha �� 0���� �ʱ�ȭ
	else if (!isShowText)
	{
		_textBufferCnt = 0; 
		_textindex = 0;
	}
	//_textAlpha�� 230 �̻��� �ʰ��ϸ� 230���� �����صα�.
	if (_textAlpha >= 230.0f) { _textAlpha = 230.0f; }
	
	
	// ���͸� ������ ���
	if (KEYMANAGER->isOnceKeyDown('Z') && isShowText)
	{
		// _textBufferCnt�� _text1.size()�� ������ �� _text1.size()�� �� ũ�ٸ�
		if (_textBufferCnt < _shopNameText.size())
		{
			// bufferCnt�� _text1.size�� ���� ���� ���� ������ �ȴ�.
			_textBufferCnt = _shopNameText.size();
		}
		// �� ���ǿ� �������� �ʴ´ٸ� _textindex�� 1�� �����ϰ� ��ư ������ �ʿ��� isShopcol�� ȣ���Ѵ�.
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

	// ��ư ��Ʈ �ڽ��� �浹���� ��� ���İ��� 230.0f�� ����, �ƴ� ��� 0���� �ʱ�ȭ
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
				TEXTDATAMANAGER->save("�κ� ���� ����.text", weapon_Selectdata);
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
				TEXTDATAMANAGER->save("�κ� ���� ����.text", weapon_Selectdata);
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
				TEXTDATAMANAGER->save("�κ� ���� ����.text", weapon_Selectdata);
				isShowText = false;
				iscollBox = false;
			}
		}
		else
		{
			_selectThreeAlpha = 0.0f;
		}
	}

	//isShopcol�� true�� �Ǹ�
	if (isShopCol)
	{
	// ���� ��ư ��Ʈ �ڽ��� ������ ���İ��� 230.0f�� �����ϰ�
		if (PtInRect(&_shopsel_OneRc, _ptMouse))
		{
			_selectOneAlpha = 230.0f;
			// ��Ŭ���� ��� ���� ��ư�� true�� �� isShopOpen�� isShowText�� false�ȴ�.
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
		
		// ���� ��ư ��Ʈ �ڽ��� ������ ���İ��� 230.0f�� �����ϰ�
		if (PtInRect(&_shopsel_TwoRc, _ptMouse))
		{
			_selectTwoAlpha = 230.0f;
			// ��Ŭ���� ��� 3���� ������ false�� �ȴ�.
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

	_shopNameText = "�װ� " + _itemName + ". ";
	_shopPriceText = "������ " + to_string(_price) + "����ε�, �췡?";
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
	FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.165, _textPosition.y*0.6, "�ձٸ��", 25, 15,
		L"����", wcslen(L"����"), RGB(255, 255, 255));

	// _textindex�� 0�϶� _chatWriteRc�������� ���� ���
	if (_textindex == 0)
	{
		FONTMANAGER->drawText(getMemDC(), _chatWriteRc, "�ձٸ��", 22, 15, shop_talk1, ((_textBufferCnt) > strlen(shop_talk1) ? strlen(shop_talk1) : (_textBufferCnt)), RGB(255, 255, 255));
	}
	// _textindex�� 1�϶� _chatWriteRc�������� ���� ���
	else if (_textindex == 1)
	{
		FONTMANAGER->drawText(getMemDC(), _chatWriteRc, "�ձٸ��", 22, 15, shop_talk2, ((_textBufferCnt) > strlen(shop_talk2) ? strlen(shop_talk2) : (_textBufferCnt)), RGB(255, 255, 255));
	}

	// isShopcol�� true�϶� ���� �ڽ� �� ���� �ڽ� �ȿ� �� �ؽ�Ʈ ���
	if (isShopCol)
	{
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _shopsel_OneRc.left, _shopsel_OneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _shopsel_TwoRc.left, _shopsel_TwoRc.top, _selectTwoAlpha);
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.80, "�ձٸ��", 22, 15,
			L"��.", wcslen(L"��."), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.86, "�ձٸ��", 22, 15,
			L"�ƴ�.", wcslen(L"�ƴ�."), RGB(255, 255, 255));
	}
	
	// shop_talk 1,2 ����
	delete[] shop_talk1;
	delete[] shop_talk2;
}

void TextSystemManager::EventLog(int arrText)
{
	_eventArrText = arrText;
	if (!iscollBox) 
	{
		IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.13, _textPosition.y*0.62, "�ձٸ��", 22, 15,
			_text[arrText].name, wcslen(_text[arrText].name), RGB(255, 255, 255));

		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.14, _textPosition.y*0.69, "�ձٸ��", 22, 15, _text[arrText].script,
			((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));
	}

	if (iscollBox)
	{
		IMAGEMANAGER->alphaRender("WP_BoxTextBox", getMemDC(), _boxChatRc.left, _boxChatRc.top, _textAlpha);

		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.1, _textPosition.y*0.69, "�ձٸ��", 22, 15, _text[arrText].script,
			((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));

		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_oneRc.left, _select_oneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_TwoRc.left, _select_TwoRc.top, _selectTwoAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_ThrRc.left, _select_ThrRc.top, _selectThreeAlpha);
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.1, _textPosition.y*0.77, "�ձٸ��", 22, 15,
			L"��", wcslen(L"��"), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.1, _textPosition.y*0.83, "�ձٸ��", 22, 15,
			L"Ȱ", wcslen(L"Ȱ"), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.1, _textPosition.y*0.89, "�ձٸ��", 22, 15,
			L"�� ��������!", wcslen(L"�� ��������!"), RGB(255, 255, 255));
		
	}
}

void TextSystemManager::AnvilLog(int arrText)
{
	_anvilArrText = arrText;

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	IMAGEMANAGER->alphaRender("AnvilNamebox", getMemDC(), _anvilNameRc.left, _anvilNameRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.59, "�ձٸ��", 22, 15,
		L"���ϴ� ����ҹ�", wcslen(L"���ϴ� ����ҹ�"), RGB(0, 0, 255));

	FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.14, _textPosition.y*0.69, "�ձٸ��", 22, 15, _text[arrText].script,
		((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));

	if (isAnvilCol)
	{
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _anvilsel_oneRc.left, _anvilsel_oneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _anvilsel_TwoRc.left, _anvilsel_TwoRc.top, _selectTwoAlpha);
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.81, "�ձٸ��", 22, 15,
			L"�����Ѵ�.", wcslen(L"�����Ѵ�."), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), _textPosition.x*0.15, _textPosition.y*0.87, "�ձٸ��", 22, 15,
			L"�����Ѵ�.", wcslen(L"�����Ѵ�."), RGB(255, 255, 255));
	}
}


#pragma once
#include "Stdafx.h"
#include "TextSystemManager.h"
#include "Player.h"
#include "LobbyPlayer.h"


HRESULT TextSystemManager::init(void)
{
	_chatImage = IMAGEMANAGER->addImage("Talkbox","Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 850, 200, true, RGB(255, 0, 255));
	_BoxchatImage = IMAGEMANAGER->addImage("WP_BoxTextBox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 850, 250, true, RGB(255, 0, 255));
	_nameImage = IMAGEMANAGER->addImage("Namebox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 125, 65, true, RGB(255, 0, 255));
	_anvilnameImage = IMAGEMANAGER->addImage("AnvilNamebox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 300, 60, true, RGB(255, 0, 255));
	_selImage = IMAGEMANAGER->addImage("SelOne", "Resource/Images/Lucie/CompleteImg/UI/SelectBox.bmp", 180, 50, true, RGB(255, 0, 255));

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

	_chatRc = RectMake(WINSIZE_X*0.08, WINSIZE_Y*0.75, _chatImage->getWidth(), _chatImage->getHeight());
	_chatWriteRc = RectMake(WINSIZE_X*0.1, WINSIZE_Y*0.77, _chatImage->getWidth(), _chatImage->getHeight());
	_boxChatRc = RectMake(WINSIZE_X*0.08, WINSIZE_Y*0.72, _chatImage->getWidth(), _chatImage->getHeight());
	_nameRc = RectMake(WINSIZE_X*0.06, WINSIZE_Y*0.68, _nameImage->getWidth(), _nameImage->getHeight());
	_anvilNameRc = RectMake(WINSIZE_X*0.06, WINSIZE_Y*0.68, _anvilnameImage->getWidth(), _anvilnameImage->getHeight());

	_shopsel_OneRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.82, _selImage->getWidth(), _selImage->getHeight());
	_shopsel_TwoRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.88, _selImage->getWidth(), _selImage->getHeight());
	_select_oneRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.79, _selImage->getWidth(), _selImage->getHeight());
	_select_TwoRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.84, _selImage->getWidth(), _selImage->getHeight());
	_select_ThrRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.89, _selImage->getWidth(), _selImage->getHeight());
	_anvilsel_oneRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.84, _selImage->getWidth(), _selImage->getHeight());
	_anvilsel_TwoRc = RectMake(WINSIZE_X*0.10, WINSIZE_Y*0.89, _selImage->getWidth(), _selImage->getHeight());

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
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && isShowText)
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
				weapon_Selectdata.push_back(_itoa(21, temp, 10));
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
				weapon_Selectdata.push_back(_itoa(24, temp, 10));
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

	//ê �α� �ڽ� ����, _chatRc�� ���� ���� ������
	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	//ê �̸� �ڽ� ����, _nameRc�� ���� ���� ������
	IMAGEMANAGER->alphaRender("Namebox", getMemDC(), _nameRc.left, _nameRc.top, _textAlpha);
	//ê �̸��ڽ� �ȿ� �ؽ�Ʈ ���
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "�ձٸ��", 27, 15,
		L"����", wcslen(L"����"), RGB(0, 0, 255));

	// _textindex�� 0�϶� _chatWriteRc�������� ���� ���
	if (_textindex == 0)
	{
		FONTMANAGER->drawText(getMemDC(), _chatWriteRc, "�ձٸ��", 27, 15, shop_talk1, ((_textBufferCnt) > strlen(shop_talk1) ? strlen(shop_talk1) : (_textBufferCnt)), RGB(255, 255, 255));
	}
	// _textindex�� 1�϶� _chatWriteRc�������� ���� ���
	else if (_textindex == 1)
	{
		FONTMANAGER->drawText(getMemDC(), _chatWriteRc, "�ձٸ��", 27, 15, shop_talk2, ((_textBufferCnt) > strlen(shop_talk2) ? strlen(shop_talk2) : (_textBufferCnt)), RGB(255, 255, 255));
	}

	// isShopcol�� true�϶� ���� �ڽ� �� ���� �ڽ� �ȿ� �� �ؽ�Ʈ ���
	if (isShopCol)
	{
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _shopsel_OneRc.left, _shopsel_OneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _shopsel_TwoRc.left, _shopsel_TwoRc.top, _selectTwoAlpha);
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.83, "�ձٸ��", 27, 15,
			L"��.", wcslen(L"��."), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.89, "�ձٸ��", 27, 15,
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
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "�ձٸ��", 27, 15,
			_text[arrText].name, wcslen(_text[arrText].name), RGB(0, 0, 255));

		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.78, "�ձٸ��", 27, 15, _text[arrText].script,
			((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));
	}

	if (iscollBox)
	{
		IMAGEMANAGER->alphaRender("WP_BoxTextBox", getMemDC(), _boxChatRc.left, _boxChatRc.top, _textAlpha);
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "�ձٸ��", 27, 15,
			_text[arrText].name, wcslen(_text[arrText].name), RGB(0, 0, 255));

		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.75, "�ձٸ��", 27, 15, _text[arrText].script,
			((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));

		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_oneRc.left, _select_oneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_TwoRc.left, _select_TwoRc.top, _selectTwoAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _select_ThrRc.left, _select_ThrRc.top, _selectThreeAlpha);
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.80, "�ձٸ��", 27, 15,
			L"��", wcslen(L"��"), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.85, "�ձٸ��", 27, 15,
			L"Ȱ", wcslen(L"Ȱ"), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.90, "�ձٸ��", 27, 15,
			L"�� ��������!", wcslen(L"�� ��������!"), RGB(255, 255, 255));
		
	}
}

void TextSystemManager::AnvilLog(int arrText)
{
	_anvilArrText = arrText;

	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	IMAGEMANAGER->alphaRender("AnvilNamebox", getMemDC(), _anvilNameRc.left, _anvilNameRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "�ձٸ��", 27, 15,
		L"���ϴ� ����ҹ�", wcslen(L"���ϴ� ����ҹ�"), RGB(0, 0, 255));

	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.78, "�ձٸ��", 27, 15, _text[arrText].script,
		((_textBufferCnt / 4) > wcslen(_text[arrText].script) ? wcslen(_text[arrText].script) : (_textBufferCnt / 4)), RGB(255, 255, 255));

	if (isAnvilCol)
	{
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _anvilsel_oneRc.left, _anvilsel_oneRc.top, _selectOneAlpha);
		IMAGEMANAGER->alphaRender("SelOne", getMemDC(), _anvilsel_TwoRc.left, _anvilsel_TwoRc.top, _selectTwoAlpha);
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.85, "�ձٸ��", 27, 15,
			L"�����Ѵ�.", wcslen(L"�����Ѵ�."), RGB(255, 255, 255));
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.11, WINSIZE_Y*0.90, "�ձٸ��", 27, 15,
			L"�����Ѵ�.", wcslen(L"�����Ѵ�."), RGB(255, 255, 255));
	}
}


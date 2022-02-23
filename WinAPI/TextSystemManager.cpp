#pragma once
#include "Stdafx.h"
#include "TextSystemManager.h"

HRESULT TextSystemManager::init(void)
{
	_Chatimage = IMAGEMANAGER->addImage("Talkbox","Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 850, 200, true, RGB(255, 0, 255));
	_Nameimage = IMAGEMANAGER->addImage("Namebox", "Resource/Images/Lucie/CompleteImg/system/textBox.bmp", 125, 65, true, RGB(255, 0, 255));

	
	_text[0] = { L"마리", L"그건 로브야. 가격은 250골드." };
	_text[1] = { L"마리", L"그건 평범한 마법사의 로브야." };

	_textBufferCnt = 0;
	_count = 0;

	_chatRc = RectMake(WINSIZE_X*0.08, WINSIZE_Y*0.75, _Chatimage->getWidth(), _Chatimage->getHeight());
	_nameRc = RectMake(WINSIZE_X*0.06, WINSIZE_Y*0.68, _Nameimage->getWidth(), _Nameimage->getHeight());
	return S_OK;
}

void TextSystemManager::release(void)
{
	//! Do Notting
}

void TextSystemManager::update(int arrNum)
{
	_textAlpha += 4.0f;
	
	if (KEYMANAGER->isStayKeyDown(VK_SPACE)) _textBufferCnt += 1;

	if (_textAlpha >= 230) _textAlpha = 230;
}

void TextSystemManager::render(int arrNum)
{
	_textIndex = arrNum;
	
	IMAGEMANAGER->alphaRender("Talkbox", getMemDC(), _chatRc.left, _chatRc.top, _textAlpha);
	IMAGEMANAGER->alphaRender("Namebox", getMemDC(), _nameRc.left, _nameRc.top, _textAlpha);
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.7, "맑은 고딕", 27, 15, 
		_text[_textIndex].name, wcslen(_text[_textIndex].name), RGB(255, 0, 255));
	
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.1, WINSIZE_Y*0.78, "맑은 고딕", 27, 15, 
		_text[_textIndex].script, ((_textBufferCnt / 4) > wcslen(_text[_textIndex].script) ? wcslen(_text[_textIndex].script) : (_textBufferCnt / 4)), RGB(255, 0, 255));


}

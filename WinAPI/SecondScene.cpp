#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("배경", "Resource/Images/1942/1942map.bmp", 1000, 2048 * 2);
	_tempSound = new TempSoundTest;
	_tempSound->init();

	_offsetX = 0;
	_offsetY = 0;
	_bgSpeed=0;
	_textBufferCnt = 0;

	return S_OK;
}

void SecondScene::release(void)
{
}

void SecondScene::update(void)
{
	_tempSound->update();
	_bgSpeed += 3;
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))_textBufferCnt += 1;
}

void SecondScene::render(HDC hdc)
{
	IMAGEMANAGER->loopRender("배경", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), 0, _bgSpeed);
	//SetBkMode() :투명하게 하는 함수(글자 뒤로 배경이 보이게 한다.)
	SetBkMode(getMemDC(), TRANSPARENT);
	char str[128];
	wsprintf(str,"기존의 폰트");
	TextOut(getMemDC(), 120, 350, str, strlen(str));


	
	// 폰트 새로운 방법
	HFONT font;
	HFONT oldFont;
	font = CreateFont(
		70, 0, 0, 0, 600, 0, 0, 1,
		HANGUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림")
	);
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	wsprintf(str, "새로운 폰트");
	TextOut(getMemDC(), 100, 400, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	//=====================fontmanager===============
	LPCWSTR script = L"포기하지 않고 하다보면 너희도 좋은 프로그래머가 될 수 있을거야! 오류좀 그만내구...";
	FONTMANAGER->drawText(getMemDC(), 30, 100, "Kostar", 25, 700, script, (((_textBufferCnt / 5) > wcslen(script)) ? wcslen(script) : (_textBufferCnt / 5)), RGB(255, 219, 50));
	
}

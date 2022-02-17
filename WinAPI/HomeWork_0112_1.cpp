#include "Stdafx.h"
#include "HomeWork_0112_1.h"

HRESULT HomeWork_0112_1::init(void)
{
	MainGame::init();

	_background = new my::Image;
	_background->init("Resource/Images/Background/background4.bmp", WINSIZE_X, WINSIZE_Y);

	_appleSprite = new my::Image;
	_appleSprite->init("Resource/Images/Homework/apple.bmp", 32, 32, true, RGB(255, 0, 255));

	_bulletSprite = new my::Image;
	_bulletSprite->init("Resource/Images/Homework/bullet.bmp", 31, 29, true, RGB(255, 0, 255));

	_cannonSprite = new my::Image;
	_cannonSprite->init("Resource/Images/Homework/cannon.bmp", 39, 45, true, RGB(255, 0, 255));

	_treeSprite = new my::Image;
	_treeSprite->init("Resource/Images/Homework/tree.bmp", 300, 490, true,RGB(255, 0, 255));
	
	_treeRect = RectMakeCenter(600, 550, 300, 490);

	return S_OK;
}

void HomeWork_0112_1::release(void)
{
	MainGame::release();

	SAFE_DELETE(_appleSprite);
	SAFE_DELETE(_bulletSprite);
	SAFE_DELETE(_cannonSprite);
	SAFE_DELETE(_treeSprite);
}

void HomeWork_0112_1::update(void)
{
	MainGame::update();

}

void HomeWork_0112_1::render(HDC hdc)
{
	HDC memDC = this->getBackBuffer()->getMemDC();
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	//========================================================

	_background->render(memDC, 0, 0);

	_appleSprite->render(memDC, 100, 0);
	_bulletSprite->render(memDC,50, 0);
	_cannonSprite->render(memDC, 0, 0);


	
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, _treeRect.left, _treeRect.top, _treeRect.right, _treeRect.bottom);
	}
	_treeSprite->render(memDC, _treeRect.left, _treeRect.top);


	//_plImage->render(memDC, _rc.left, _rc.top);

	//========================================================
	//백버퍼의 내용을 hdc에 그린다.
	this->getBackBuffer()->render(hdc, 0, 0);
}



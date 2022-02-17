#include "Stdafx.h"
#include "GameClass_0112.h"

HRESULT GameClass_0112::init(void)
{
	MainGame::init();

	IMAGEMANAGER->addImage("데드스페이스", "Resource/Images/Background/background4.bmp", WINSIZE_X, WINSIZE_Y);

	_alphaA =0, _alphaNum =1;
	return S_OK;
}

void GameClass_0112::release(void)
{
	MainGame::release();

}

void GameClass_0112::update(void)
{
	MainGame::update();

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료 확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	_alphaA += _alphaNum;
	if (_alphaA <= 0 || _alphaA >= 255) _alphaNum = _alphaNum * -1;


}

void GameClass_0112::render()
{
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	//========================================================

	IMAGEMANAGER->alphaRender("데드스페이스",getMemDC(),0,0,_alphaA);

	//========================================================
	//백버퍼의 내용을 hdc에 그린다.
	this->getBackBuffer()->render(getHDC());
}

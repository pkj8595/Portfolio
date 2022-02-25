#include "Stdafx.h"
#include "Lobby.h"
#include "TextSystemManager.h"

HRESULT Lobby::init(void)
{
	IMAGEMANAGER->addImage("Lobby", "Resource/Images/Lucie/CompleteImg/ground/map/ground12.bmp", 1008, 1065);
	_p_rc = RectMake(CENTER_X, CENTER_Y, 25, 25);
	_Bookrc = RectMake(CENTER_X - 60, CENTER_Y + 50, 30, 30);
	_Boxrc = RectMake(CENTER_X - 240, CENTER_Y, 50, 100);

	_tsm = new TextSystemManager;
	_tsm->init();

	collBox = false;
	return S_OK;
}

void Lobby::release(void)
{
	_tsm->release();
}

void Lobby::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)&& _p_rc.right < WINSIZE_X - 410)
	{
		_p_rc.left += 5;
		_p_rc.right += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)&& _p_rc.left > 315)
	{
		_p_rc.left -= 5;
		_p_rc.right -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)&& _p_rc.top > 425)
	{
		_p_rc.top -= 5;
		_p_rc.bottom -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)&& _p_rc.bottom < WINSIZE_Y - 295)
	{
		_p_rc.top += 5;
		_p_rc.bottom += 5;
	}
	collision();
	_tsm->update();
}

void Lobby::render(void)
{
	IMAGEMANAGER->render("Lobby", getMemDC());
	Rectangle(getMemDC(), _Bookrc.left, _Bookrc.top, _Bookrc.right, _Bookrc.bottom);
	Rectangle(getMemDC(), _Boxrc.left, _Boxrc.top, _Boxrc.right, _Boxrc.bottom);
	Rectangle(getMemDC(), _p_rc.left, _p_rc.top, _p_rc.right, _p_rc.bottom);
	
	if (collBox) _tsm->shopLog(L"·Îºê", L"250");

}

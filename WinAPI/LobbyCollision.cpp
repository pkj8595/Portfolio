#include "Stdafx.h"
#include "Lobby.h"

void Lobby::LobbyCollision()
{
	COLORREF color = GetPixel(IMAGEMANAGER->findImage("col_Lobby")->getMemDC(), _player->getRect().left + 50, _player->getRect().top + 200);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	if (!(r == 255 && g == 255 && b == 255))
	{
		_player->setCollision();
	}

}
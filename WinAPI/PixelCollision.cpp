#include "Stdafx.h"
#include "PlayScene.h"

void PlayScene::pixelCollision()
{
	COLORREF color = GetPixel(_mapManager->getCurrentMapPixel()->getMemDC(), _player->getRect().left, _player->getRect().top);
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	if (!(r == 255 && g == 255 && b == 255))
	{
		_player->setCollision();
	}

	if (_player->getPosition().x < 0 && _mapManager->getCurrentMap()->isClear())
	{
		_mapManager->changeMap(0);
		_player->setPosition(_mapManager->getCurrentMapPixel()->getWidth() - 350, _player->getPosition().y);
	}
	if (_player->getPosition().x > _mapManager->getCurrentMapPixel()->getWidth() && _mapManager->getCurrentMap()->isClear())
	{
		_mapManager->changeMap(1);
		_player->setPosition(350, _player->getPosition().y);
	}
	if (_player->getPosition().y < 0 && _mapManager->getCurrentMap()->isClear())
	{
		_mapManager->changeMap(2);
		_player->setPosition(_player->getPosition().x, _mapManager->getCurrentMapPixel()->getHeight() - 200);
	}
	if (_player->getPosition().y > _mapManager->getCurrentMapPixel()->getHeight() && _mapManager->getCurrentMap()->isClear())
	{
		_mapManager->changeMap(3);
		_player->setPosition(_player->getPosition().x, 200);
	}
}
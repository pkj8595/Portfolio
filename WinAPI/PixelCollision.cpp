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

}
void PlayScene::changeMapFadeOut()
{
	if (_isChanging) return;
	if (_player->getPosition().x < 0 && _mapManager->getCurrentMap()->isClear())
	{
		_isChanging = true;
		_changeScreenType = 0;
	}
	if (_player->getPosition().x > _mapManager->getCurrentMapPixel()->getWidth() && _mapManager->getCurrentMap()->isClear())
	{
		_isChanging = true;
		_changeScreenType = 1;
	}
	if (_player->getPosition().y < 0 && _mapManager->getCurrentMap()->isClear())
	{
		_isChanging = true;
		_changeScreenType = 2;
	}
	if (_player->getPosition().y > _mapManager->getCurrentMapPixel()->getHeight() && _mapManager->getCurrentMap()->isClear())
	{
		_isChanging = true;
		_changeScreenType = 3;
	}
}
void PlayScene::setFadeOutAlpha()
{
	
	if (_isChanging)
	{
		_fadeoutAlpha += 4;
	}
	else if (!_isChanging && _fadeoutAlpha > 0)
	{
		_fadeoutAlpha -= 4;
	}
	if (_fadeoutAlpha > 252)
	{
		_isChanging = false;
	}
}

void PlayScene::changeMap()
{
	if (_changeScreenType == 0 && _isChanging && _fadeoutAlpha > 250)
	{
		_mapManager->changeMap(0);
		spawnMonster();
		if (_mapManager->getCurrentMap()->getMapType() == Map::MAPTYPE::SHOP)
			_player->setPosition(600, 306);
		else _player->setPosition(_mapManager->getCurrentMapPixel()->getWidth() - 350, _player->getPosition().y);
		_isChanging = false;
	}
	if (_changeScreenType == 1 && _isChanging && _fadeoutAlpha > 250)
	{
		_mapManager->changeMap(1);
		spawnMonster();
		if (_mapManager->getCurrentMap()->getMapType() == Map::MAPTYPE::SHOP)
			_player->setPosition(600, 306);
		else _player->setPosition(350, _player->getPosition().y);
		_isChanging = false;
	}
	if (_changeScreenType == 2 && _isChanging && _fadeoutAlpha > 250)
	{
		_mapManager->changeMap(2);
		spawnMonster();
		if (_mapManager->getCurrentMap()->getMapType() == Map::MAPTYPE::SHOP)
			_player->setPosition(600, 306);
		else _player->setPosition(_player->getPosition().x, _mapManager->getCurrentMapPixel()->getHeight() - 200);
		_isChanging = false;
	}
	if (_changeScreenType == 3 && _isChanging && _fadeoutAlpha > 250)
	{
		_mapManager->changeMap(3);
		spawnMonster();
		if (_mapManager->getCurrentMap()->getMapType() == Map::MAPTYPE::SHOP)
			_player->setPosition(600, 306);
		else _player->setPosition(_player->getPosition().x, 200);
		_isChanging = false;
	}

	if (_enemyManager->checkClear())
	{
		_mapManager->getCurrentMap()->setClear(true);
	}
}

void PlayScene::spawnMonster()
{
	if (_mapManager->getCurrentMap()->getType() == Map::MAPTYPE::DEFAULT &&
		!_mapManager->getCurrentMap()->isClear())
	{
		_enemyManager->setMinion();
	}
}

void PlayScene::checkPlayerEscapeWithoutClear()
{
	if (_mapManager->getCurrentMap()->isClear())
	{
		if (_player->getX() < _mapManager->getCurrentMap()->getMapRC().left && !_mapManager->getCurrentMap()->isConnected(0)) 
			_player->setX(_mapManager->getCurrentMap()->getMapRC().left);
		if (_player->getX() > _mapManager->getCurrentMap()->getMapRC().right && !_mapManager->getCurrentMap()->isConnected(2))
			_player->setX(_mapManager->getCurrentMap()->getMapRC().right);
		if (_player->getY() < _mapManager->getCurrentMap()->getMapRC().top && !_mapManager->getCurrentMap()->isConnected(1))
			_player->setY(_mapManager->getCurrentMap()->getMapRC().top);
		if (_player->getY() > _mapManager->getCurrentMap()->getMapRC().bottom && !_mapManager->getCurrentMap()->isConnected(3))
			_player->setY(_mapManager->getCurrentMap()->getMapRC().bottom);
	}
	else
	{
		if (_player->getX() < _mapManager->getCurrentMap()->getMapRC().left) 
			_player->setX(_mapManager->getCurrentMap()->getMapRC().left);
		if (_player->getX() > _mapManager->getCurrentMap()->getMapRC().right) 
			_player->setX(_mapManager->getCurrentMap()->getMapRC().right);
		if (_player->getY() < _mapManager->getCurrentMap()->getMapRC().top) 
			_player->setY(_mapManager->getCurrentMap()->getMapRC().top);
		if (_player->getY() > _mapManager->getCurrentMap()->getMapRC().bottom) _player->setY(_mapManager->getCurrentMap()->getMapRC().bottom);
	}

}
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
void PlayScene::pixelBulletCollision()
{
	for (int i = 0; i < _player->getNormalWeapon()->getWeapon().size(); i++)
	{
		COLORREF color = GetPixel(_mapManager->getCurrentMapPixel()->getMemDC(), 
											_player->getNormalWeapon()->getPoint(i).x, _player->getNormalWeapon()->getPoint(i).y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 255 && b == 255))
		{
			RECT temp = RectMakeCenter(_player->getNormalWeapon()->getPoint(i).x, _player->getNormalWeapon()->getPoint(i).y,
				48, 48);
			_effectManager->createEffect("NormalHit", temp, 0.05f);
			_player->getNormalWeapon()->removeBullet(i);
		}
	}
	for (int i = 0; i < _player->getBowWeapon()->getWeapon().size(); i++)
	{
		COLORREF color = GetPixel(_mapManager->getCurrentMapPixel()->getMemDC(),
			_player->getBowWeapon()->getPoint(i).x, _player->getBowWeapon()->getPoint(i).y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 255 && b == 255))
		{
			RECT temp = RectMakeCenter(_player->getBowWeapon()->getPoint(i).x, _player->getBowWeapon()->getPoint(i).y,
				48, 48);
			_effectManager->createEffect("BowHit", temp, 0.05f);
			_player->getBowWeapon()->removeBullet(i);
		}
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
		else _player->setPosition(450, 430);
		_isChanging = false;
	}
	if (_changeScreenType == 1 && _isChanging && _fadeoutAlpha > 250)
	{
		_mapManager->changeMap(1);
		spawnMonster();
		if (_mapManager->getCurrentMap()->getMapType() == Map::MAPTYPE::SHOP)
			_player->setPosition(600, 306);
		else _player->setPosition(450, 430);
		_isChanging = false;
	}
	if (_changeScreenType == 2 && _isChanging && _fadeoutAlpha > 250)
	{
		_mapManager->changeMap(2);
		spawnMonster();
		if (_mapManager->getCurrentMap()->getMapType() == Map::MAPTYPE::SHOP)
			_player->setPosition(600, 306);
		else _player->setPosition(450, 430);
		_isChanging = false;
	}
	if (_changeScreenType == 3 && _isChanging && _fadeoutAlpha > 250)
	{
		_mapManager->changeMap(3);
		spawnMonster();
		if (_mapManager->getCurrentMap()->getMapType() == Map::MAPTYPE::SHOP)
			_player->setPosition(600, 306);
		else _player->setPosition(450, 430);
		_isChanging = false;
	}

	if (_enemyManager->checkClear())
	{
		_mapManager->getCurrentMap()->setClear(true);
		if (_mapManager->getCurrentMap()->getMapType() == Map::MAPTYPE::BOSS)
		{
			_showBossEffect = true;
		}
	}
}

void PlayScene::spawnMonster()
{
	if (_mapManager->getCurrentMap()->getType() == Map::MAPTYPE::DEFAULT &&
		!_mapManager->getCurrentMap()->isClear())
	{
		_enemyManager->setMinion();
	}
	else if (_mapManager->getCurrentMap()->getType() == Map::MAPTYPE::BOSS &&
		!_mapManager->getCurrentMap()->isClear())
	{
		_enemyManager->setBoss();
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

void PlayScene::checkDead()
{
	if (_player->isDead())
	{
		if (_deadTimer == 0) _deadTimer = TIMEMANAGER->getWorldTime();

		if (_deadAlpha > 255) _deadAlpha = 255;
		else if (_deadAlpha < 255) _deadAlpha ++;
	}
	if (_deadTimer != 0 && _deadTimer + 10.0f < TIMEMANAGER->getWorldTime())
	{
		release();
		SCENEMANAGER->changeScene("Lobby");
	}
}
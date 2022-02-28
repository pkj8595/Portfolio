#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "Player.h"
#include "Slime.h"
#include "KingSlime.h"
#include "BigSlime.h"
#include "Snake.h"
#include "Rafflesia.h"
#include "ForestFairy.h"

bool EnemyManager::checkClear()
{
	if (_vMinion.size() == 0) return true;
	else return false;
}

EnemyManager::EnemyManager(){
	//DO NOTTING
}

EnemyManager::~EnemyManager(){
	//DO NOTTING
}

HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("해파리", "Resource/Images/Rocket/jelly.bmp", 0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("enemy1", "Resource/Images/Project/enemy1.bmp", 0.0f, 0.0f, 256, 32, 8, 1, true, RGB(15, 15, 15));
	IMAGEMANAGER->addFrameImage("enemy2", "Resource/Images/Project/enemy2.bmp", 0.0f, 0.0f, 256, 32, 8, 1, true, RGB(15, 15, 15));
	IMAGEMANAGER->addFrameImage("enemy3", "Resource/Images/Project/enemy3.bmp", 0.0f, 0.0f, 256, 32, 8, 1, true, RGB(15, 15, 15));

	IMAGEMANAGER->addFrameImage("bullet16", "Resource/Images/Project/bullet16.bmp", 0.0f, 0.0f, 256, 16, 16, 1, true, RGB(255, 0,255));
	IMAGEMANAGER->addFrameImage("bullet3030", "Resource/Images/Project/bullet3030.bmp", 0.0f, 0.0f, 192, 30, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("적 미사일", "Resource/Images/Rocket/bullet.bmp", 7 , 7 , true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Slime", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Slime2.bmp", 288, 2016, 3, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Snake", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Snake.bmp", 144, 624, 3, 13, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Rafflesia", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Rafflesia.bmp", 240, 549, 3, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ForestFairy", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Forestfairy.bmp", 168, 930, 3, 10, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("KingSlime", "Resource/Images/Lucie/CompleteImg/Enemy/Boss/KingSlime1.bmp", 1080, 7560, 3, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BigSlime", "Resource/Images/Lucie/CompleteImg/Enemy/Boss/KingSlime1.bmp", 576, 4032, 3, 21, true, RGB(255, 0, 255));
	
	
	


	//미니언 생성

	_bullet = new Bullet;
	_bullet->init("bullet16",30,1000);

	_efm = new EffectManager;
	_efm->init();

	return S_OK;
}

void EnemyManager::release(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion) 
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}

	_bullet->release();
	SAFE_DELETE(_bullet);
}

void EnemyManager::update(void)
{
	_viMinion = _vMinion.begin();
	for (;_viMinion != _vMinion.end(); ++_viMinion) 
	{
		(*_viMinion)->update();
		(*_viMinion)->setPlayerPos(_pPlayer->getPosition());
		(*_viMinion)->setPlayer(*_pPlayer);
	}
	checkActive();

	_efm->update();
	//minionBulletFire();
	//_bullet->update();
}

void EnemyManager::render(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	//_bullet->render();
	_efm->render();
}

void EnemyManager::setMinion(void)
{
	/*int temp = RND->getInt(3);
	switch (temp)
	{
	case 0: {
		Enemy* slime;
		slime = new Slime;
		slime->init("Slime", PointMake(CENTER_X, CENTER_Y));
		_vMinion.push_back(slime);

		Enemy* rafflesia;
		rafflesia = new Rafflesia;
		rafflesia->init("Rafflesia", PointMake(CENTER_X - 150, CENTER_Y + 30));
		_vMinion.push_back(rafflesia);

		Enemy* slime2;
		slime2 = new Slime;
		slime2->init("Slime", PointMake(CENTER_X - 50, CENTER_Y - 50));
		_vMinion.push_back(slime2);
	}break;

	case 1: {
		Enemy* slime;
		slime = new Slime;
		slime->init("Slime", PointMake(CENTER_X, CENTER_Y));
		_vMinion.push_back(slime);

		Enemy* snake;
		snake = new Snake;
		snake->init("Snake", PointMake(CENTER_X - 100, CENTER_Y));
		_vMinion.push_back(snake);
	} break;

	case 2: {
		Enemy* snake;
		snake = new Snake;
		snake->init("Snake", PointMake(CENTER_X + 100, CENTER_Y));
		_vMinion.push_back(snake);

		Enemy* snake2;
		snake2 = new Snake;
		snake2->init("Snake", PointMake(CENTER_X - 100, CENTER_Y));
		_vMinion.push_back(snake2);
	} break;
	}*/

	//Enemy* rafflesia;
	//rafflesia = new Rafflesia;
	//rafflesia->init("Rafflesia", PointMake(CENTER_X - 150, CENTER_Y + 30));
	//_vMinion.push_back(rafflesia);

	Enemy* forestFairy;
	forestFairy = new ForestFairy;
	forestFairy->init("ForestFairy", PointMake(CENTER_X, CENTER_Y - 100));
	_vMinion.push_back(forestFairy);
}

void EnemyManager::setBoss(void)
{
	Enemy* kingslime;
	kingslime = new KingSlime;
	kingslime->init("KingSlime", PointMake(CENTER_X, CENTER_Y));
	_vMinion.push_back(kingslime);
}

void EnemyManager::setMiniBoss(int x, int y)
{
	Enemy* bigslime;
	bigslime = new BigSlime;
	bigslime->init("BigSlime", PointMake(x + 10, y));
	bigslime->setHpY(0);
	_vMinion.push_back(bigslime);

	Enemy* bigslime2;
	bigslime2 = new BigSlime;
	bigslime2->init("BigSlime", PointMake(x - 10, y));
	bigslime2->setHpY(35);
	_vMinion.push_back(bigslime2);
}

void EnemyManager::setSlime(int x, int y)
{
	Enemy* slime;
	slime = new Slime;
	slime->init("Slime", PointMake(x + 10, y));
	_vMinion.push_back(slime);
	Enemy* slime2;

	Enemy* slime3;
	slime3 = new Slime;
	slime3->init("Slime", PointMake(x - 10, y));
	_vMinion.push_back(slime3);
}



void EnemyManager::removeMinion(int arrNum)
{
	_vMinion[arrNum]->release();
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

//리스너를 사용하는 것이 좋아보이긴한다. 
void EnemyManager::checkActive(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if (!(*_viMinion)->getIsActive()) 
		{
			if ((*_viMinion)->isBoss())
			{
				POINT temp = { (*_viMinion)->getRect().left + ((*_viMinion)->getRect().right - (*_viMinion)->getRect().left) / 2,
					(*_viMinion)->getRect().top + ((*_viMinion)->getRect().bottom - (*_viMinion)->getRect().top )/2 };
				(*_viMinion)->release();
				SAFE_DELETE(*_viMinion);
				_viMinion = _vMinion.erase(_viMinion);
				setMiniBoss(temp.x, temp.y);
				break;
			}
			else if ((*_viMinion)->isMiniBoss())
			{
				POINT temp = { (*_viMinion)->getRect().left + ((*_viMinion)->getRect().right - (*_viMinion)->getRect().left) / 2,
								(*_viMinion)->getRect().top + ((*_viMinion)->getRect().bottom - (*_viMinion)->getRect().top) / 2 };
				(*_viMinion)->release();
				SAFE_DELETE(*_viMinion);
				_viMinion = _vMinion.erase(_viMinion);
				setSlime(temp.x, temp.y);
				break;
			}
			else
			{
				_efm->createEffect("Dead", (*_viMinion)->getRect(), 0.002f);
				_pPlayer->addExp((*_viMinion)->getExp());
				(*_viMinion)->release();
				SAFE_DELETE(*_viMinion);
				_viMinion = _vMinion.erase(_viMinion);
				break;
			}
		}
	}
}

void EnemyManager::minionBulletFire(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire()) 
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right - rc.left) / 2,
						rc.bottom + (rc.top - rc.bottom) / 2,
						_pPlayer->getPosition().x,
						_pPlayer->getPosition().y),
				RND->getFromFloatTo(2.0f, 4.0f));
		}
	}
}

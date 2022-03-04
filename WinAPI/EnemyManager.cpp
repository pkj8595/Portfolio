#include "Stdafx.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Slime.h"
#include "KingSlime.h"
#include "BigSlime.h"
#include "Snake.h"
#include "Rafflesia.h"
#include "ForestFairy.h"
#include "MushMan.h"
#include "Mushroom.h"
#include "ItemSpawner.h"

bool EnemyManager::checkClear()
{
	if (_vMinion.size() == 0) return true;
	else return false;
}

EnemyManager::EnemyManager()
{
	//DO NOTTING
}

EnemyManager::~EnemyManager()
{
	//DO NOTTING
}

HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("Slime", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Slime2.bmp", 288, 2016, 3, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Snake", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Snake.bmp", 144, 624, 3, 13, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Rafflesia", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Rafflesia.bmp", 240, 549, 3, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ForestFairy", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Forestfairy.bmp", 168, 930, 3, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MushMan", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Mushman.bmp", 384, 550, 8, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Mushroom", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Mushroom.bmp", 13, 13, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("KingSlime", "Resource/Images/Lucie/CompleteImg/Enemy/Boss/KingSlime1.bmp", 1080, 7560, 3, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BigSlime", "Resource/Images/Lucie/CompleteImg/Enemy/Boss/KingSlime1.bmp", 576, 4032, 3, 21, true, RGB(255, 0, 255));




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

}

void EnemyManager::update(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
		(*_viMinion)->setPlayerPos(_pPlayer->getPosition());
		(*_viMinion)->setPlayer(*_pPlayer);
	}
	checkActive();

	_efm->update();
}

void EnemyManager::render(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_efm->render();
}

void EnemyManager::setMinion(void)
{
	int temp = RND->getInt(4);
	switch (temp)
	{
	case 0: {
		Enemy* slime;
		slime = new Slime;
		slime->init("Slime", PointMake(CAMERAMANAGER->getDisplayCenterX(), CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(slime);

		Enemy* rafflesia;
		rafflesia = new Rafflesia;
		rafflesia->init("Rafflesia", PointMake(CAMERAMANAGER->getDisplayCenterX() - 150, CAMERAMANAGER->getDisplayCenterY() + 30));
		_vMinion.push_back(rafflesia);

		Enemy* slime2;
		slime2 = new Slime;
		slime2->init("Slime", PointMake(CAMERAMANAGER->getDisplayCenterX() - 50, CAMERAMANAGER->getDisplayCenterY() - 50));
		_vMinion.push_back(slime2);

		Enemy* forestFairy;
		forestFairy = new ForestFairy;
		forestFairy->init("ForestFairy",
			PointMake(CAMERAMANAGER->getDisplayCenterX() + 70,
				CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(forestFairy);
	}break;

	case 1: {
		Enemy* slime;
		slime = new Slime;
		slime->init("Slime", PointMake(CAMERAMANAGER->getDisplayCenterX(), CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(slime);

		Enemy* snake;
		snake = new Snake;
		snake->init("Snake", PointMake(CAMERAMANAGER->getDisplayCenterX() - 100, CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(snake);

		Enemy* forestFairy;
		forestFairy = new ForestFairy;
		forestFairy->init("ForestFairy",
			PointMake(CAMERAMANAGER->getDisplayCenterX() + 70,
				CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(forestFairy);
	} break;

	case 2: {
		Enemy* snake;
		snake = new Snake;
		snake->init("Snake", PointMake(CAMERAMANAGER->getDisplayCenterX() + 100, CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(snake);

		Enemy* snake2;
		snake2 = new Snake;
		snake2->init("Snake", PointMake(CAMERAMANAGER->getDisplayCenterX() - 100, CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(snake2);

		Enemy* forestFairy;
		forestFairy = new ForestFairy;
		forestFairy->init("ForestFairy",
			PointMake(CAMERAMANAGER->getDisplayCenterX() + 70,
				CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(forestFairy);
	} break;

	case 3: {
		Enemy* mushman;
		mushman = new MushMan;
		mushman->init("MushMan", PointMake(CAMERAMANAGER->getDisplayCenterX() - 30,
			CAMERAMANAGER->getDisplayCenterY() + 150));
		_vMinion.push_back(mushman);

		Enemy* forestFairy;
		forestFairy = new ForestFairy;
		forestFairy->init("ForestFairy",
			PointMake(CAMERAMANAGER->getDisplayCenterX() + 70,
				CAMERAMANAGER->getDisplayCenterY()));
		_vMinion.push_back(forestFairy);
	} break;
	}
	//Enemy* forestFairy;
	//forestFairy = new ForestFairy;
	//forestFairy->init("ForestFairy",
	//	PointMake(CAMERAMANAGER->getDisplayCenterX() + 70,
	//		CAMERAMANAGER->getDisplayCenterY()));
	//_vMinion.push_back(forestFairy);

	//Enemy* mushman;
	//mushman = new MushMan;
	//mushman->init("MushMan", PointMake(CAMERAMANAGER->getDisplayCenterX() - 30,
	//	CAMERAMANAGER->getDisplayCenterY() + 150));
	//_vMinion.push_back(mushman);
}

void EnemyManager::setBoss(void)
{
	Enemy* kingslime;
	kingslime = new KingSlime;
	kingslime->init("KingSlime",
		PointMake(CAMERAMANAGER->getDisplayCenterX(),
			CAMERAMANAGER->getDisplayCenterX()));
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
					(*_viMinion)->getRect().top + ((*_viMinion)->getRect().bottom - (*_viMinion)->getRect().top) / 2 };
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
				if (RND->getInt(2) == 0)
				{
					ItemSpawner::getSingleton()->createItem((*_viMinion)->getX(), (*_viMinion)->getY(), true);
				}
				_pPlayer->addExp((*_viMinion)->getExp());
				(*_viMinion)->release();
				SAFE_DELETE(*_viMinion);
				_viMinion = _vMinion.erase(_viMinion);
				TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/mobdead.wav");
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

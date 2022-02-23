#include "Stdafx.h"
#include "EnemyManager.h"
#include "Minion.h"
#include "CProjectPlayer.h"
#include "Slime.h"
#include "Snake.h"

EnemyManager::EnemyManager(){
	//DO NOTTING
}

EnemyManager::~EnemyManager(){
	//DO NOTTING
}

HRESULT EnemyManager::init(void)
{
	IMAGEMANAGER->addFrameImage("���ĸ�", "Resource/Images/Rocket/jelly.bmp", 0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("enemy1", "Resource/Images/Project/enemy1.bmp", 0.0f, 0.0f, 256, 32, 8, 1, true, RGB(15, 15, 15));
	IMAGEMANAGER->addFrameImage("enemy2", "Resource/Images/Project/enemy2.bmp", 0.0f, 0.0f, 256, 32, 8, 1, true, RGB(15, 15, 15));
	IMAGEMANAGER->addFrameImage("enemy3", "Resource/Images/Project/enemy3.bmp", 0.0f, 0.0f, 256, 32, 8, 1, true, RGB(15, 15, 15));

	IMAGEMANAGER->addFrameImage("bullet16", "Resource/Images/Project/bullet16.bmp", 0.0f, 0.0f, 256, 16, 16, 1, true, RGB(255, 0,255));
	IMAGEMANAGER->addFrameImage("bullet3030", "Resource/Images/Project/bullet3030.bmp", 0.0f, 0.0f, 192, 30, 6, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�� �̻���", "Resource/Images/Rocket/bullet.bmp", 7 , 7 , true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Slime", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Slime2.bmp", 288, 2016, 3, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Snake", "Resource/Images/Lucie/CompleteImg/Enemy/Monster/Snake.bmp", 144, 624, 3, 13, true, RGB(255, 0, 255));


	//�̴Ͼ� ����
	setMinion();

	_bullet = new Bullet;
	_bullet->init("bullet16",30,1000);

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
		(*_viMinion)->setPlayer(_pPlayer);

	}
	//checkActive();
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
}

void EnemyManager::setMinion(void)
{
	//for (int i = 0; i < 2; i++)
	//{
	//	for (int  j = 0; j < 10; j++)
	//	{
	//		Enemy* minion;
	//		minion = new Minion;
	//		minion->init("enemy1", PointMake(50 + j * 50, 100 + i * 100));
	//		_vMinion.push_back(minion);
	//	}
	//}

	Enemy* slime;
	slime = new Slime;
	slime->init("Slime", PointMake(CENTER_X, CENTER_Y));
	_vMinion.push_back(slime);

	Enemy* snake;
	snake = new Snake;
	snake->init("Snake", PointMake(CENTER_X - 200, CENTER_Y));
	_vMinion.push_back(snake);
}

void EnemyManager::removeMinion(int arrNum)
{
	_vMinion[arrNum]->release();
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

//�����ʸ� ����ϴ� ���� ���ƺ��̱��Ѵ�. 
void EnemyManager::checkActive(void)
{
	_viMinion = _vMinion.begin();
	for (; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if (!(*_viMinion)->getIsActive()) 
		{
			(*_viMinion)->release();
			SAFE_DELETE(*_viMinion);
			_viMinion = _vMinion.erase(_viMinion);
			break;
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

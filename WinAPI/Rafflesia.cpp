#include "Stdafx.h"
#include "Rafflesia.h"

Rafflesia::Rafflesia()
{
}

Rafflesia::~Rafflesia()
{
}

HRESULT Rafflesia::init(const char * imageName, POINT position)
{
	Enemy::init(imageName, position);
	_x = position.x;
	_y = position.y;
	_hp = 100;
	_range = 250;
	_deadForOb = false;
	_state = RAFFLESIASTATE::RA_IDLE;

	_attackWorldTime = TIMEMANAGER->getWorldTime();
	_attackPosCheckTime = TIMEMANAGER->getWorldTime();
	_deadTimeCount = TIMEMANAGER->getWorldTime();

	_bullet = new ThornBullet;
	_bullet->init(1, 300);

	IMAGEMANAGER->addImage("GenerateRange","Resource/Images/Lucie/CompleteImg/Enemy/Monster/check.bmp", 77, 74, true, RGB(255, 0, 255));
	
	return S_OK;
}

void Rafflesia::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	Enemy::release();
}

void Rafflesia::update(void)
{
	Enemy::update();
	_bullet->update();

	if (!_deadForOb)
	{
		if (PlayerCheck())
		{
			attackPosCheck();

			//АјАн
			_state = RAFFLESIASTATE::RA_ATTACK;

		}
		else
			_state = RAFFLESIASTATE::RA_IDLE;
	}
	else
	{
		_state = RAFFLESIASTATE::RA_DEAD;
	}

	frame();

}

void Rafflesia::render(void)
{
	Enemy::render();
	_bullet->render();
}

void Rafflesia::move(void)
{
}

void Rafflesia::draw(void)
{
	_image->frameRender(getMemDC(),
		_rc.left - CAMERAMANAGER->getCameraRect().left,
		_rc.top - CAMERAMANAGER->getCameraRect().top,
		_currentFrameX,_currentFrameY);

	if (_attackPositionCheck) 
	{
		IMAGEMANAGER->alphaRender("GenerateRange", getMemDC(),
			_playerPosX - 30 - CAMERAMANAGER->getCameraRect().left,
			_playerPosY - 30 - CAMERAMANAGER->getCameraRect().top,100);
	}
}

void Rafflesia::animation(void)
{
	if (0.6f + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		
		_currentFrameX++;
		if (_currentFrameX > _image->getMaxFrameX())
		{
			_currentFrameX = 0;
		}

		if (_state == RAFFLESIASTATE::RA_DEAD)
		{
			_currentFrameX = 0;
			_currentFrameY = 8;

			if (6.f + _deadTimeCount < TIMEMANAGER->getWorldTime())
			{
				_isActive = false;
			}
		}
		
		_image->setFrameX(_currentFrameX);
	}
}

void Rafflesia::frame()
{
	switch (_state)
	{
	case RAFFLESIASTATE::RA_IDLE:
		_currentFrameY = 0;
		break;

	case RAFFLESIASTATE::RA_ATTACK:
		_currentFrameY = 4;
		attack();
		break;

	case RAFFLESIASTATE::RA_DEAD:
		_currentFrameY = 8;
		break;
	}
}

bool Rafflesia::PlayerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
	{
		return true;
	}

	_attackPositionCheck = false;
	return false;
}

void Rafflesia::attack()
{
	if (4.8f + _attackWorldTime < TIMEMANAGER->getWorldTime())
	{
		_attackWorldTime = TIMEMANAGER->getWorldTime();
		_bullet->fire(_playerPosX, _playerPosY);

		_attackPositionCheck = false;
	}
}

void Rafflesia::attackPosCheck()
{
	if (4.f + _attackPosCheckTime < TIMEMANAGER->getWorldTime())
	{
		_attackPosCheckTime = TIMEMANAGER->getWorldTime();
		_playerPosX = _playerPos.x + RAFFLESIA_BULLET_SIZE_X;
		_playerPosY = _playerPos.y + RAFFLESIA_BULLET_SIZE_Y;

		_attackPositionCheck = true;
		return;
	}
}

STObservedData Rafflesia::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_deadForOb;
	temp.damage = &_attack;
	return temp;
}

void Rafflesia::collideObject(STObservedData obData)
{
	if (((*obData.typeKey) == ObservedType::PLAYER_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD)
		&& (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
			_deadForOb = true;
		}
		else
		{
			_hp -= (*obData.damage);
		}
		(*obData.isActive) = false;
	}
}

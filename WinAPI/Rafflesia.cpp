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
	_range = 250;
	_deadForOb = false;
	_state = RAFFLESIASTATE::RA_IDLE;

	_bullet = new ThornBullet;
	_bullet->init(5, 500);

	return S_OK;
}

void Rafflesia::release(void)
{
	Enemy::release();
	_bullet->release();
}

void Rafflesia::update(void)
{
	Enemy::update();
	_bullet->update();

	if (PlayerCheck())
	{
		//공격
		_state = RAFFLESIASTATE::RA_ATTACK;
	}
	else
		_state = RAFFLESIASTATE::RA_IDLE;

	frame();

	float angle = getAngle(_x, _y, _playerPos.x, _playerPos.y);

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_bullet->fire(_x, _y, angle);
	}

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
	_image->frameRender(getMemDC(), _rc.left, _rc.top,_currentFrameX,_currentFrameY);
	IMAGEMANAGER->render("bulletCheck", getMemDC(), _rc.left, _rc.left);
	_bullet->draw();
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

		_image->setFrameX(_currentFrameX);
	}
}

void Rafflesia::frame()
{
	switch (_state)
	{
	case RAFFLESIASTATE::RA_IDLE:
		_currentFrameY = 0;
		//cout << "IDLE" << endl;
		break;

	case RAFFLESIASTATE::RA_ATTACK:
		_currentFrameY = 4;
		//cout << "ATTACK" << endl;
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

	return false;
}

void Rafflesia::attack()
{
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
	if (((*obData.typeKey) == ObservedType::ROCKET_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD)
		&& (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
			//나중에 죽는 애니메이션 넣는걸로 바꿀 것. isActive를 false로 바꾸는 작업은 죽은 애니메이션 전부 실행 뒤 바꿔주는 것으로 변경	
			_deadForOb = true;
		}
		else
		{
			_hp -= (*obData.damage);
		}
		(*obData.isActive) = false;
	}
}

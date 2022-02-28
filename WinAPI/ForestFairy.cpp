#include "Stdafx.h"
#include "ForestFairy.h"

ForestFairy::ForestFairy()
{
}

ForestFairy::~ForestFairy()
{
}

HRESULT ForestFairy::init(const char * imageName, POINT position)
{
	Enemy::init(imageName, position);
	_x = position.x;
	_y = position.y;
	_hp = 100.0f;
	_speed = 0.3f;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_range = 220;
	_frameSpeed = 0.3f;

	_deadTimeCount = TIMEMANAGER->getWorldTime();
	_moveWorldTime = TIMEMANAGER->getWorldTime();

	_deadForOb = false;

	return S_OK;
}

void ForestFairy::release(void)
{
	Enemy::release();

}

void ForestFairy::update(void)
{
	Enemy::update();

	if (!_deadForOb)
	{
		if (playerCheck())
		{	
			_state = FAIRYSTATE::FA_ATTAACK;
		}
		else
		 randomPosCreate();
	}
	else
	{
	}

	frame();

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void ForestFairy::render(void)
{
	Enemy::render();
}

void ForestFairy::move(void)
{
}

void ForestFairy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void ForestFairy::animation(void)
{
	if (_frameSpeed + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;

		if (_state == FAIRYSTATE::FA_DEAD)
		{
			_currentFrameX = 0;
			_currentFrameY = 8;

			if (6.f + _deadTimeCount < TIMEMANAGER->getWorldTime())
			{
				_isActive = false;
			}
		}
		else
		{
			if (_currentFrameX >= _image->getMaxFrameX())
			{
				_currentFrameX = 0;
			}
		}

		_image->setFrameX(_currentFrameX);
	}
}

void ForestFairy::randomPosCreate()
{
	_state = FAIRYSTATE::FA_MOVE;

	if (_rndTimeCount + _moveWorldTime < TIMEMANAGER->getWorldTime())
	{
		_moveWorldTime = TIMEMANAGER->getWorldTime();
		_randomX = RND->getInt(3) - 1;
		_randomY = RND->getInt(3) - 1;
	}

	//좌표에 따라 모션 변경
	//왼쪽 || 왼쪽 아래 || 왼쪽 위
	if (_randomX == -1 || _randomX == -1 && _randomY == -1 || _randomX == -1 && _randomY == 1)
	{
		_direction = FAIRYDIRECTION::FA_LEFT;
	}

	//오른쪽 || 오른쪽 아래 || 오른쪽 위
	if (_randomX == 1 || _randomX == 1 && _randomY == -1 || _randomX == 1 && _randomY == 1)
	{
		_direction = FAIRYDIRECTION::FA_RIGHT;
	}

	//위
	if (_randomY == -1 && _randomX == 0)
	{
		_direction = FAIRYDIRECTION::FA_UP;
	}

	//아래
	if (_randomY == 1 && _randomX == 0)
	{
		_direction = FAIRYDIRECTION::FA_DOWN;
	}

	if (_randomX == 0 && _randomY == 0)
	{
		_randomX = RND->getInt(3) - 1;
		_randomY = RND->getInt(3) - 1;
	}
}

void ForestFairy::randomMove()
{
	if (MONSTER_MOVE_RANGE_LEFT <= _x && _rc.left <= MONSTER_MOVE_RANGE_RIGHT)
	{
		_x += _randomX * _speed;
	}

	if (MONSTER_MOVE_RANGE_UP <= _rc.top && _rc.top <= MONSTER_MOVE_RANGE_DOWN)
	{
		_y += _randomY * _speed;
	}
}

void ForestFairy::attack()
{

}

bool ForestFairy::playerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
	{
		return true;
	}

	return false;
}

void ForestFairy::frame()
{
	switch (_state)
	{
	case FAIRYSTATE::FA_MOVE:
		switch (_direction)
		{
		case FAIRYDIRECTION::FA_LEFT:
			_currentFrameY = 1;
			break;

		case FAIRYDIRECTION::FA_RIGHT:
			_currentFrameY = 2;
			break;

		case FAIRYDIRECTION::FA_UP:
			_currentFrameY = 3;
			break;

		case FAIRYDIRECTION::FA_DOWN:
			_currentFrameY = 0;
			break;
		}
		randomMove();
		break;

	case FAIRYSTATE::FA_ATTAACK:
		switch (_direction)
		{
		case FAIRYDIRECTION::FA_LEFT:
			_currentFrameY = 5;
			break;

		case FAIRYDIRECTION::FA_RIGHT:
			_currentFrameY = 6;
			break;

		case FAIRYDIRECTION::FA_UP:
			_currentFrameY = 7;
			break;

		case FAIRYDIRECTION::FA_DOWN:
			_currentFrameY = 4;
			break;
		}
		attack();
		break;

	case FAIRYSTATE::FA_DEAD:
		_currentFrameX = 0;
		_currentFrameY = 8;
		break;
	}
}

STObservedData ForestFairy::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_deadForOb;
	temp.damage = &_attack;
	return temp;
}

void ForestFairy::collideObject(STObservedData obData)
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

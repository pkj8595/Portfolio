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
	_angle = 0.0f;
	_playerDistance = 0.0f;
	_attackDistance = 0.0f;
	_randomX = _randomY = 0;
	_deadTimeCount = TIMEMANAGER->getWorldTime();
	_moveWorldTime = TIMEMANAGER->getWorldTime();
	_deadForOb = false;
	_attackCoolTime = 0;

	_normalBullet = new NormalBullet;
	_normalBullet->init(10, 350);
	_fairyBullet = new FairyBullet;
	_fairyBullet->init(1, 300);
	_bubbleBullet = new BubbleBullet;
	_bubbleBullet->init(30, 350);

	return S_OK;
}

void ForestFairy::release(void)
{
	_normalBullet->release();
	SAFE_DELETE(_normalBullet);

	_fairyBullet->release();
	SAFE_DELETE(_fairyBullet);

	_bubbleBullet->release();
	SAFE_DELETE(_bubbleBullet);

	Enemy::release();

}

void ForestFairy::update(void)
{
	Enemy::update();
	_normalBullet->update();
	_fairyBullet->update();
	_bubbleBullet->update();

	if (!_deadForOb)
	{
		if (playerCheck() && _attackCoolTime <= 0)
		{
			_state = FAIRYSTATE::FA_ATTACK;
		}
		else randomPosCreate();
	}
	else
	{
		_state = FAIRYSTATE::FA_DEAD;
	}

	frame();

	_rc = RectMakeCenter(_x - CAMERAMANAGER->getCameraRect().left, _y - CAMERAMANAGER->getCameraRect().top, _image->getFrameWidth(), _image->getFrameHeight());
}

void ForestFairy::render(void)
{
	Enemy::render();

	if (_isActive)
	{
		frame();
		draw();
	}
}

void ForestFairy::move(void)
{
}

void ForestFairy::draw(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
	_normalBullet->render();
	_fairyBullet->render();
	_bubbleBullet->render();
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

void ForestFairy::attack()
{

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

	case FAIRYSTATE::FA_ATTACK:
		switch (_attackParttern)
		{
		case FAIRYATTACK::FA_NORMAL:
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
			normalBullet();
			break;

		case FAIRYATTACK::FA_FAIRY:
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
			fariyBullet();
			break;

		case FAIRYATTACK::FA_BUBBLE:
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
			bubbleBullet();
			break;
		}
		break;

	case FAIRYSTATE::FA_DEAD:
		_currentFrameX = 0;
		_currentFrameY = 8;
		break;
	}
}

void ForestFairy::randomPosCreate()
{
	_attackCoolTime--;
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

bool ForestFairy::playerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
	{
		return true;
	}

	return false;
}

void ForestFairy::normalBullet()
{

	if (_attackParttern == FAIRYATTACK::FA_NORMAL&&_image->getMaxFrameX() - 1 == _currentFrameX)
	{
		float tempAngle = getAngle(_x, _y, _playerPos.x + 50, _playerPos.y + 50);
		for (int i = 0; i < 12; i++)
		{
			cout << (0.5*tempAngle) * i * PI / 180 << endl;
			_normalBullet->fire(_x, _y, (tempAngle) + (i * PI / 180), 2.0f, 0);
		}
		for (int i = 0; i < 4; i++)
		{
			_normalBullet->fire(_x, _y, ((tempAngle) + (i * PI / 180)) - 50, 1.94f, 0);
			_normalBullet->fire(_x, _y, (tempAngle) + (i * PI / 180), 1.94f, 0);
		}
		for (int i = 0; i < 2; i++)
		{
			_normalBullet->fire(_x, _y, ((tempAngle) + (i * PI / 180)) - 50, 1.9f, 0);
			_normalBullet->fire(_x, _y - 25, (tempAngle) + (i * PI / 180), 1.9f, 0);
		}
		for (int i = 0; i < 1; i++)
		{
			_normalBullet->fire(_x, _y, ((tempAngle) + (i * PI / 180)) - 50, 1.86f, 0);
			_normalBullet->fire(_x, _y - 25, (tempAngle) + (i * PI / 180), 1.86f, 0);
		}

		_attackCoolTime = 300;

		//더이상 다음 상태가 될 때까지 공격 X되게 하는 구문 필요
	}
}

void ForestFairy::fariyBullet()
{
	//_attackCoolTime = 500;

	if (_attackParttern == FAIRYATTACK::FA_FAIRY&&_image->getMaxFrameX() - 1 == _currentFrameX)
	{
		//for (int i = 0; i < 1; i++)

		_fairyBullet->fire(_x, _y, 30 * PI / 180);
		_attackCoolTime = 100;

	}
}

void ForestFairy::bubbleBullet()
{
	if (_attackParttern == FAIRYATTACK::FA_BUBBLE&&_image->getMaxFrameX() - 1 == _currentFrameX)
	{
		float tempAngle = getAngle(_x, _y, _playerPos.x + 50, _playerPos.y + 50);

		for (int i = 0; i < 30; i++)
		{
			_bubbleBullet->fire(_x, _y, tempAngle * i * PI / 180, 2.0f, 30 * PI / 180);
			_attackCoolTime = 100;
		}
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

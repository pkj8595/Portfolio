#include "Stdafx.h"
#include "Snake.h"

Snake::Snake()
{
}

Snake::~Snake()
{
}

HRESULT Snake::init(const char * imageName, POINT position)
{
	Enemy::init(imageName, position);
	_x = position.x;
	_y = position.y;
	_moveWorldTime = TIMEMANAGER->getWorldTime();
	_playerDistance = 0.0f;
	_range = 0;
	_randomX = 0;
	_randomY = 0;
	_speed = 0.5f;
	_frameSpeed = 0.3f;

	_threeDirBullet = new ThreeDirectionMissile;
	_threeDirBullet->init(3, 300);

	_twoDirBullet = new TwoDirectionMissile;
	_twoDirBullet->init(2, 300);
	
	return S_OK;
}

void Snake::release(void)
{
	_threeDirBullet->release();
	SAFE_DELETE(_threeDirBullet);

	_twoDirBullet->release();
	SAFE_DELETE(_twoDirBullet);
	Enemy::release();
}

void Snake::update(void)
{
	Enemy::update();
	_threeDirBullet->update();
	_twoDirBullet->update();

	//randomPosCreate();
	//randomMove();


	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_state = SNAKESTATE::SN_MOVE;
		_direction = SNAKEDIRECTION::SN_LEFT;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_state = SNAKESTATE::SN_MOVE;
		_direction = SNAKEDIRECTION::SN_RIGHT;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_state = SNAKESTATE::SN_MOVE;
		_direction = SNAKEDIRECTION::SN_UP;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_state = SNAKESTATE::SN_MOVE;
		_direction = SNAKEDIRECTION::SN_DOWN;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Snake::render(void)
{
	Enemy::render();

	_threeDirBullet->render();
	_twoDirBullet->render();
}

void Snake::move(void)
{
}

void Snake::draw(void)
{
	frame();
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void Snake::animation(void)
{
	if (_frameSpeed + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;

		if (_currentFrameX >= _maxFrameX)
		{
			_currentFrameX = 0;
		}

		_image->setFrameX(_currentFrameX);
	}

}

void Snake::randomPosCreate()
{
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
		_direction = SNAKEDIRECTION::SN_LEFT;
	}

	//오른쪽 || 오른쪽 아래 || 오른쪽 위
	if (_randomX == 1 || _randomX == 1 && _randomY == -1 || _randomX == 1 && _randomY == 1)
	{
		_direction = SNAKEDIRECTION::SN_RIGHT;
	}

	//위
	if (_randomY == -1 && _randomX == 0)
	{
		_direction = SNAKEDIRECTION::SN_UP;
	}

	//아래
	if (_randomY == 1 && _randomX == 0)
	{
		_direction = SNAKEDIRECTION::SN_DOWN;
	}

	//움직이지 않을경우
	if (_randomX == 0 && _randomY == 0)
	{
		_state = SNAKESTATE::SN_IDLE;
	}
	else
		_state = SNAKESTATE::SN_MOVE;
}

void Snake::randomMove()
{
	if (MONSTER_MOVE_RANGE_LEFT <= _x &&  _rc.left <= MONSTER_MOVE_RANGE_RIGHT)
	{
		_x += _randomX * _speed;
	}

	if (MONSTER_MOVE_RANGE_UP <= _rc.top && _rc.top <= MONSTER_MOVE_RANGE_DOWN)
	{
		_y += _randomY * _speed;
	}
}

void Snake::attack()
{
	//_stae = SNAMESTATE::SNAKE_ATTACK;

	//if (2 + _worldTime < TIMEMANAGER->getWorldTime())
	//{
	//	_worldTime = TIMEMANAGER->getWorldTime();
	//	_twobullet->fire(_x, _y, getAngle(_x, _y, _playerPos.x, _playerPos.y));
	//}

	//if (1 + _worldTime < TIMEMANAGER->getWorldTime())
	//{
	//	_worldTime = TIMEMANAGER->getWorldTime();
	//	_threebullet->fire(_x, _y, getAngle(_x, _y, _playerPos.x, _playerPos.y));
	//}
}

bool Snake::playerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
		return true;

	return false;
}

void Snake::frame()
{
	switch (_state)
	{
	case SNAKESTATE::SN_IDLE:
		switch (_direction)
		{
		case SNAKEDIRECTION::SN_LEFT:
			_currentFrameY = 9;
			break;

		case SNAKEDIRECTION::SN_RIGHT:
			_currentFrameY = 10;
			break;

		case SNAKEDIRECTION::SN_UP:
			_currentFrameY = 11;
			break;

		case SNAKEDIRECTION::SN_DOWN:
			_currentFrameY = 8;
			break;
		}
		_maxFrameX = 2;
		break;

	case SNAKESTATE::SN_MOVE:
		switch (_direction)
		{
		case SNAKEDIRECTION::SN_LEFT:
			_currentFrameY = 1;
			break;

		case SNAKEDIRECTION::SN_RIGHT:
			_currentFrameY = 2;
			break;

		case SNAKEDIRECTION::SN_UP:
			_currentFrameY = 3;
			break;

		case SNAKEDIRECTION::SN_DOWN:
			_currentFrameY = 0;
			break;
		}
		_maxFrameX = 3;
		break;

	case SNAKESTATE::SN_ATTACK:
		switch (_direction)
		{
		case SNAKEDIRECTION::SN_LEFT:
			_currentFrameY = 5;
			break;

		case SNAKEDIRECTION::SN_RIGHT:
			_currentFrameY = 6;
			break;

		case SNAKEDIRECTION::SN_UP:
			_currentFrameY = 7;
			break;

		case SNAKEDIRECTION::SN_DOWN:
			_currentFrameY = 6;
			break;
		}
		_maxFrameX = 3;
		break;
	}
	
}

STObservedData Snake::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_isActive;
	temp.damage = &_attack;
	return temp;
}

void Snake::collideObject(STObservedData obData)
{
	if ((*obData.typeKey) == ObservedType::ROCKET_MISSILE && (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
			//나중에 죽는 애니메이션 넣는걸로 바꿀 것.  isActive를 false로 바꾸는 작업은 죽은 애니메이션 전부 실행 뒤 바꿔주는 것으로 변경
			_isActive = false;
		}
		else
		{
			_hp -= (*obData.damage);
			(*obData.isActive) = false;
		}
	}
}

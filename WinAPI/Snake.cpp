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
	_speed = 1.f;
	_time = 150;
	_range = 300;
	_angle = 0.0f;
	_moveCheck = true;
	attRange = 150;
	_attTime = 2;
	_worldTime = TIMEMANAGER->getWorldTime();

	_ani = new Animation;
	_ani->init(_image->getWidth(), _image->getHeight(), 48, 48);
	_ani->setDefPlayFrame(false, true);
	_ani->setFPS(2);
	_ani->AniStart();

	_threebullet = new ThreeDirectionMissile;
	_threebullet->init(3, 300);

	_twobullet = new TwoDirectionMissile;
	_twobullet->init(2, 300);
	
	return S_OK;
}

void Snake::release(void)
{

}

void Snake::update(void)
{
	Enemy::update();
	_threebullet->update();
	_twobullet->update();

	//플레이어가 일정 범위에 들어왔다면
	if (playerCheck())
	{
		_angle = getAngle(_x, _y, _playerPos.x, _playerPos.y);
		_x += cosf(_angle) * _speed;
		_y += -sinf(_angle) * _speed;

		//슬라임 왼쪽
		if (_playerPos.x > _x)
		{
			_direction = SNAKEDIRECTION::SNAKE_RIGHT;
		}

		////슬라임 오른쪽
		if (_playerPos.x < _x)
		{
			_direction = SNAKEDIRECTION::SNAKE_LEFT;
		}

		////슬라임 밑
		if (_playerPos.y < _y)
		{
			_direction = SNAKEDIRECTION::SNAKE_UP;
		}

		////슬라임 위
		if (_playerPos.y > _y)
		{
			_direction = SNAKEDIRECTION::SNAKE_DOWN;
		}

			//_stae = SNAMESTATE::SNAKE_MOVE;
			_angle = getAngle(_x, _y, _playerPos.x, _playerPos.y);
			_x += cosf(_angle) * _speed;
			_y += -sinf(_angle) * _speed;

		//공격 사거리 안으로 들어왔을 경우
		if (_playerDistance < attRange)
		{
			//공격 실행
			attack();
		}
	}
	else
	{
		randomMove();
	}

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Snake::render(void)
{
	Enemy::render();

	_threebullet->render();
	_twobullet->render();
}

void Snake::move(void)
{
}

void Snake::draw(void)
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _ani);
}

void Snake::animation(void)
{
	switch (_direction)
	{
	case SNAKEDIRECTION::SNAKE_LEFT: //왼쪽일 때
		switch (_stae)
		{
		case SNAMESTATE::SNAKE_IDLE:
			_ani->setPlayFrame(24,26, false, true);
			break;

		case SNAMESTATE::SNAKE_MOVE:
			_ani->setPlayFrame(3,6, false, true);
			break;

		case SNAMESTATE::SNAKE_ATTACK:
			_ani->setPlayFrame(15,17, false, true);
			break;
		}
		break;

	case SNAKEDIRECTION::SNAKE_RIGHT: //오른쪽일 때
		switch (_stae)
		{
		case SNAMESTATE::SNAKE_IDLE:
			_ani->setPlayFrame(30,32, false, true);
			break;

		case SNAMESTATE::SNAKE_MOVE:
			_ani->setPlayFrame(6,9, false, true);
			break;

		case SNAMESTATE::SNAKE_ATTACK:
			_ani->setPlayFrame(18,21, false, true);
			break;
		}
		break;

	case SNAKEDIRECTION::SNAKE_UP: //위쪽
		switch (_stae)
		{
		case SNAMESTATE::SNAKE_IDLE:
			_ani->setPlayFrame(33,35, false, true);
			break;

		case SNAMESTATE::SNAKE_MOVE:
			_ani->setPlayFrame(9,12, false, true);
			break;

		case SNAMESTATE::SNAKE_ATTACK:
			_ani->setPlayFrame(21,24, false, true);
			break;
		}
		break;

	case SNAKEDIRECTION::SNAKE_DOWN: //아래쪽
		switch (_stae)
		{
		case SNAMESTATE::SNAKE_IDLE:
			_ani->setPlayFrame(24,26, false, true);
			break;

		case SNAMESTATE::SNAKE_MOVE:
			_ani->setPlayFrame(0,3, false, true);
			break;

		case SNAMESTATE::SNAKE_ATTACK:
			_ani->setPlayFrame(12,15, false, true);
			break;
		}
		break;
	}
}

void Snake::randomMove()
{
	if (_time <= 0) //확인용
	{
		randomX = RND->getInt(3) - 1;
		randomY = RND->getInt(3) - 1;
		_time = 150;
	}
	_time--;

	//if (_moveRange < getDistance(_x, _y, _x + 150, _y + 150))
	//{
		//randomX = RND->getInt(3) - 1;
		//randomY = RND->getInt(3) - 1;
	//}

	_x += randomX * _speed;
	_y += randomY * _speed;

	if (randomX == -1)
	{
		_direction = SNAKEDIRECTION::SNAKE_LEFT;
		_stae = SNAMESTATE::SNAKE_MOVE;
	}

	else if (randomX == 1)
	{
		_direction = SNAKEDIRECTION::SNAKE_RIGHT;
		_stae = SNAMESTATE::SNAKE_MOVE;
	}

	else if (randomY == -1)
	{
		_direction = SNAKEDIRECTION::SNAKE_UP;
		_stae = SNAMESTATE::SNAKE_MOVE;
	}

	else  if (randomY == 1)
	{
		_direction = SNAKEDIRECTION::SNAKE_DOWN;
		_stae = SNAMESTATE::SNAKE_MOVE;
	}

	else
	{
		_direction = _direction;
		_stae = SNAMESTATE::SNAKE_IDLE;
	}
}

void Snake::attack()
{
	_stae = SNAMESTATE::SNAKE_ATTACK;

	if (2 + _worldTime < TIMEMANAGER->getWorldTime())
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_twobullet->fire(_x, _y, getAngle(_x, _y, _playerPos.x, _playerPos.y));
	}

	if (1 + _worldTime < TIMEMANAGER->getWorldTime())
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_threebullet->fire(_x, _y, getAngle(_x, _y, _playerPos.x, _playerPos.y));
	}
}

bool Snake::playerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
		return true;

	return false;
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

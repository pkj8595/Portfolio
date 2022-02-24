#include "Stdafx.h"
#include "Slime.h"

Slime::Slime()
{
}

Slime::~Slime()
{
}

HRESULT Slime::init(const char * imageName, POINT position)
{
	Enemy::init(imageName,position);

	_x = position.x;
	_y = position.y;
	_randomX = 0;
	_randomY = 0;
	_speed = 0.5f;
	_worldTime = TIMEMANAGER->getWorldTime();
	_frameSpeed = 0.3f;
	_index = 0;
	_frameY = 0;
	_randomTimeCount = RND->getFromFloatTo(0.f,2.f);
	_moveTimeCount = TIMEMANAGER->getWorldTime();
	_playerDistance = 0.0f;
	_range = 0.0f;
	_moveCheck = true;

	_direction = SLIMEDIRECTION::SM_DOWN;
	_state = SLIMESTATE::SM_IDLE;

	return S_OK;
}

void Slime::release(void)
{
	Enemy::release();
}

void Slime::update(void)
{
	Enemy::update();

	if(playerCheck())
	{

	}
	else
	{
		//랜덤좌표 생성
		if (1 + _moveTimeCount < TIMEMANAGER->getWorldTime())
		{
			_moveTimeCount = TIMEMANAGER->getWorldTime();

			_randomX = RND->getInt(3) - 1;
			_randomY = RND->getInt(3) - 1;
		}

		//좌표에 따라 모션 변경
		if (_randomX == -1 || _randomX == -1 && _randomY == 0 || _randomX == -1 && _randomY == -1 || _randomX == -1 && _randomY == 1)
		{
			_direction = SLIMEDIRECTION::SM_LEFT;
		}

		if (_randomX == 1 || _randomX == 1 && _randomY == 0 || _randomX == 1 && _randomY == -1 || _randomX == 1 && _randomY == 1)
		{
			_direction = SLIMEDIRECTION::SM_RIGHT;
		}

		if (_randomY == -1 || _randomY == -1 && _randomX == 0)
		{
			_direction = SLIMEDIRECTION::SM_UP;
		}

		if (_randomY == 1 || _randomY == 1 && _randomX == 0)
		{
			_direction = SLIMEDIRECTION::SM_DOWN;
		}

		if (_randomX == 0 && _randomY == 0)
		{
			_state = SLIMESTATE::SM_IDLE;
		}
		else
			_state = SLIMESTATE::SM_MOVE;
	}

	frame();
	cout << "Slime::update(void) 랜덤X:" << _randomX << endl;
	cout << "Slime::update(void) 랜덤Y:" << _randomY << endl;

	//system("pause");

	/*_slimebullet->update();
	_slimeCirclebullet->update();

	//플레이어가 일정 범위에 들어왔다면
	if (playerCheck())
	{
	
		if (_moveCheck)
		{
			_slimestate = SLIMESTATE::SM_MOVE;
			_angle = getAngle(_x, _y, _playerPos.x, _playerPos.y);
			_x += cosf(_angle) * _speed;
			_y += -sinf(_angle) * _speed;
		}

		//공격 사거리 안으로 들어왔을 경우
		if (_playerDistance < attRange)
		{	
			_moveCheck = false;
			
			//공격 실행
			attack();
		}
	}
	else
	{
		_moveCheck = true;
		randomMove();
	}

	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());*/
}

void Slime::render(void)
{
	//Enemy::render();
	draw();
	animation();
	//_slimebullet->render();
	//_slimeCirclebullet->render();
}

void Slime::move(void)
{

}

void Slime::draw(void)
{
	////_image->frameRender(getMemDC(), _rc.left, _rc.top);
	_image->frameRender(getMemDC(), _rc.left, _rc.top);

	////Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	////cout << "랜덤X:" << randomX << endl;
	//cout << "Slime::draw(void):" << _ani->getFrameIdx() << endl;

	////Sleep(1000);
	////system("pause");
}

void Slime::frame()
{
	switch (_state)
	{
	case SLIMESTATE::SM_IDLE:
		switch (_direction)
		{
		case SLIMEDIRECTION::SM_LEFT:
			_frameY = 1;
			break;

		case SLIMEDIRECTION::SM_RIGHT:
			_frameY = 2;
			break;

		case SLIMEDIRECTION::SM_UP:
			_frameY = 3;
			break;

		case SLIMEDIRECTION::SM_DOWN:
			_frameY = 0;
			break;
		}
		break;

	case SLIMESTATE::SM_MOVE:
		switch (_direction)
		{
		case SLIMEDIRECTION::SM_LEFT:
			_frameY = 5;
			_moveCheck = true;
			randomMove();
			break;

		case SLIMEDIRECTION::SM_RIGHT:
			_frameY = 6;
			_moveCheck = true;
			randomMove();
			break;

		case SLIMEDIRECTION::SM_UP:
			_frameY = 4;
			_moveCheck = true;
			randomMove();
			break;

		case SLIMEDIRECTION::SM_DOWN:
			_frameY = 7;
			_moveCheck = true;
			randomMove();
			break;
		}
		break;

	case SLIMESTATE::SM_ATTACK:
		switch (_direction)
		{
		case SLIMEDIRECTION::SM_LEFT:
			break;

		case SLIMEDIRECTION::SM_RIGHT:
			break;

		case SLIMEDIRECTION::SM_UP:
			break;

		case SLIMEDIRECTION::SM_DOWN:
			break;
		}
		break;
	}
}

void Slime::animation()
{
	if (_frameSpeed + _worldTime <= TIMEMANAGER->getWorldTime())
	{
		_worldTime = TIMEMANAGER->getWorldTime();
		_image->setFrameY(_frameY);
		_index++;

		if (_index > _image->getMaxFrameX())
			_index = 0;

		_image->setFrameX(_index);
	}
}

void Slime::randomValue(int i)
{

}

void Slime::randomMove()
{
	if (_moveCheck)
	{
		_x += _randomX * _speed;
		_y -= _randomY * _speed;

		_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	}
}

/*void Slime::attack()
{	
	_slimestate = slimestate::sm_attack;

	if (_ani->getframeidx() == 26 || _ani->getframeidx() == 35 || _ani->getframeidx() == 32 || _ani->getframeidx() == 29)
	{
		if (_ani->isplay())
		{
			//_ani->anipause();
			_slimecirclebullet->fire(_x, _y);
			//attrange /= 2;
			//
			//if (attrange < 0)
			//	attrange = 0;
		}
	}
}*/

bool Slime::playerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
		return true;

	return false;
}

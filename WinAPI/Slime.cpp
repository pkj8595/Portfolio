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
	_speed = 1.f;
	_time = 150;
	_range = 300;
	_angle = 0.0f;

	_moveRange = 30;
	_attTime = 2;
	_moveCheck = true;
	_worldTime = TIMEMANAGER->getWorldTime();
	attRange = 150;
	_attCheck = false;

	_ani = new Animation;
	_ani->init(_image->getWidth(), _image->getHeight(),96,96);
	_ani->setFPS(5);
	_ani->setDefPlayFrame(false, true);
	_ani->AniStart();


	_slimebullet = new ThreeDirectionMissile;
	_slimebullet->init(3, 300);

	_slimeCirclebullet = new CircleMissile;
	_slimeCirclebullet->init(10,300);

	return S_OK;
}

void Slime::release(void)
{
	Enemy::release();
}

void Slime::update(void)
{
	Enemy::update();
	_slimebullet->update();
	_slimeCirclebullet->update();

	//플레이어가 일정 범위에 들어왔다면
	if (playerCheck())
	{
		//슬라임 왼쪽
		if (_playerPos.x > _x )
		{
			_slimeDir = SLIMEDIRECTION::SM_RIGHT;
		}
		
		//슬라임 오른쪽
		 if (_playerPos.x < _x )
		{
			 _slimeDir = SLIMEDIRECTION::SM_LEFT;
		}

		//슬라임 밑
		 if (_playerPos.y < _y )
		{
			 _slimeDir = SLIMEDIRECTION::SM_UP;
		}
		
		//슬라임 위
		 if (_playerPos.y > _y)
		{
			 _slimeDir = SLIMEDIRECTION::SM_DOWN;
		}
		
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
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void Slime::render(void)
{
	Enemy::render();
	_slimebullet->render();
	_slimeCirclebullet->render();
}

void Slime::move(void)
{

}

void Slime::draw(void)
{
	//_image->frameRender(getMemDC(), _rc.left, _rc.top);
	_image->aniRender(getMemDC(),_rc.left,_rc.top, _ani);

	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	//cout << "랜덤X:" << randomX << endl;
	cout << "인덱스:" << _ani->getFrameIdx() << endl;

	//Sleep(1000);
	//system("pause");
}

void Slime::animation()
{
	switch (_slimeDir)
	{
	case SLIMEDIRECTION::SM_LEFT: //왼쪽일 때
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
				_ani->setPlayFrame(3, 6, false, true);
			break;
		
		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(15, 18, false, true);
			break;
		
		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(27, 30, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_RIGHT: //오른쪽일 때
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
				_ani->setPlayFrame(6, 9, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(18, 21, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(30, 33, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_UP: //위쪽
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
			_ani->setPlayFrame(9, 12, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(21, 24, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(33, 36, false, true);
			break;
		}
		break;

	case SLIMEDIRECTION::SM_DOWN: //아래쪽
		switch (_slimestate)
		{
		case SLIMESTATE::SM_IDLE:
			_ani->setPlayFrame(0, 3, false, true);
			break;

		case SLIMESTATE::SM_MOVE:
			_ani->setPlayFrame(12, 15, false, true);
			break;

		case SLIMESTATE::SM_ATTACK:
			_ani->setPlayFrame(24, 27, false, true);
			break;
		}
		break;
	}
}

void Slime::attack()
{	
	_slimestate = SLIMESTATE::SM_ATTACK;

	if (_ani->getFrameIdx() == 26 || _ani->getFrameIdx() == 35 || _ani->getFrameIdx() == 32 || _ani->getFrameIdx() == 29)
	{
		if (_ani->isPlay())
		{
			//_ani->AniPause();
			_slimeCirclebullet->fire(_x, _y);
			//attRange /= 2;
			//
			//if (attRange < 0)
			//	attRange = 0;
		}
	}		
}

void Slime::randomMove()
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
		_slimeDir = SLIMEDIRECTION::SM_LEFT;
		_slimestate = SLIMESTATE::SM_MOVE;
	}

	else if (randomX == 1)
	{
		_slimeDir = SLIMEDIRECTION::SM_RIGHT;
		_slimestate = SLIMESTATE::SM_MOVE;
	}

	else if (randomY == -1)
	{
		_slimeDir = SLIMEDIRECTION::SM_UP;
		_slimestate = SLIMESTATE::SM_MOVE;
	}

	else  if (randomY == 1)
	{
		_slimeDir = SLIMEDIRECTION::SM_DOWN;
		_slimestate = SLIMESTATE::SM_MOVE;
	}

	else
	{
		_slimeDir = _slimeDir;
		_slimestate = SLIMESTATE::SM_IDLE;
	}
}

bool Slime::playerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
		return true;

	return false;
}

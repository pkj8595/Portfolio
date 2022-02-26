#include "Stdafx.h"
#include "KingSlime.h"

HRESULT KingSlime::init(const char * imageName, POINT position)
{
	Enemy::init(imageName, position);
	_type = ObservedType::MINION;
	
	_state = STATE::STOP;
	_direction = DIRECTION::DOWN;

	_alreadyShot = false;
	_angle = 0;
	
	_hp = 500;
	_x = position.x;
	_y = position.y;
	_frameX = _frameY = 0;
	_frameSet = 0;

	_stopSet = 6;
	_stopSet = 2;
	_walkRndSet = RND->getFromIntTo(3, 6);
	_attackSet = 0;


	_deadForOb = false;
	_isActive = true;

	_frameDelayTime = TIMEMANAGER->getWorldTime();


	_normalBullet = new NormalBullet;
	_normalBullet->init(100, 500);

	_bubbleBullet = new BubbleBullet;
	_bubbleBullet->init(100, 500);

	/*	이후 공격탄막 추가
	_bounceBullet = new BounceBullet;
	_bounceBullet->init();
	*/
	return S_OK;
}

void KingSlime::release(void)
{

}

void KingSlime::update(void)
{
	_normalBullet->update();
	_bubbleBullet->update();
	_angle = getAngle(_x, _y, _playerPos.x, _playerPos.y);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	setDirection();
	frameUpdate();
	move();
}

void KingSlime::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, _frameY);

	_normalBullet->render();
	_bubbleBullet->render();
}

STObservedData KingSlime::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_deadForOb;
	temp.damage = &_attack;
	return temp;
}

void KingSlime::collideObject(STObservedData obData)
{
}

void KingSlime::frameUpdate()
{
	if (_frameDelayTime + 0.3 < TIMEMANAGER->getWorldTime())
	{
		_frameX++;
		_frameX = _frameX % 3;
		if (_frameX == 0) _frameSet++;
		_frameDelayTime = TIMEMANAGER->getWorldTime();
	}
}

void KingSlime::setDirection()
{
	if (_angle >= 0 && _angle < 45 * PI / 180) _direction = DIRECTION::RIGHT; 
	else if (_angle >= 45*PI/180 && _angle < 135 * PI / 180) _direction = DIRECTION::UP;
	else if (_angle >= 135*PI/180 && _angle < 225 * PI / 180) _direction = DIRECTION::LEFT;
	else if (_angle >= 225*PI/180 && _angle < 315 * PI / 180) _direction = DIRECTION::DOWN;
	else _direction = DIRECTION::RIGHT;
	changeDirectionState();
}

void KingSlime::move()
{
	switch (_state)
	{
	case STATE::STOP :
	{
		if (_frameSet > _stopSet) changeAnotherState();
	} break;
	case STATE::WALK:
	{
		_x += cosf(_angle) * 0.8f;
		_y += -sinf(_angle) * 0.8f;
		if (_frameSet > _walkRndSet) changeAnotherState();
	} break;
	case STATE::ATTACK_NORMAL:
	{
		if (_frameX == 2 && !_alreadyShot)
		{
			int tempRnd = RND->getInt(3);
			float tempRotate;
			if (tempRnd == 0) tempRotate = 0;
			else if (tempRnd == 1) tempRotate = -0.3 * PI / 180;
			else tempRotate = 0.3 * PI / 180;

			for (int i = 0; i < 20; i++)
			{
				_normalBullet->fire(_x, _y + 80, 18 * i * PI / 180, 2.8f, tempRotate);
			}
			for (int i = 0; i < 10; i++)
			{
				_normalBullet->fire(_x, _y + 80, 36 * i * PI / 180, 4.0f, tempRotate * (-1));
			}
			_alreadyShot = true;
		}
		if (_frameSet > _attackSet) changeAnotherState();
	} break;
	case STATE::ATTACK_BUBBLE:
	{
		if (_frameX == 2 && !_alreadyShot)
		{
			for (int i = 0; i < 80; i++)
			{
				_bubbleBullet->fire(_x, _y + 80, 45 * (i / 10) * PI / 180, 3.0f, (PI * 2 / 10) * i);
			}
			_alreadyShot = true;
		}
		if (_frameSet > _attackSet) changeAnotherState();
	} break;
	case STATE::ATTACK_BOUNCE:
	{

		if (_frameSet > _attackSet) changeAnotherState();
	} break;
	}
}

void KingSlime::changeState(STATE state)
{
	_state = state;
	_frameSet = 0;
	switch (state)
	{
	case STATE::STOP:
	{
		_frameY = static_cast<int>(_direction);
	} break;
	case STATE::WALK:
	{
		_alreadyShot = false;
		_walkRndSet = RND->getFromIntTo(5, 10);
	} break;
	case STATE::ATTACK_NORMAL:
	{
	} break;
	case STATE::ATTACK_BUBBLE:
	{
	} break;
	case STATE::ATTACK_BOUNCE:
	{
	} break;
	}
}

void KingSlime::changeDirectionState()
{
	switch (_state)
	{
	case STATE::STOP:
	{
		_frameY = static_cast<int>(_direction);
	} break;
	case STATE::WALK:
	{
		_frameY = static_cast<int>(_direction) + 4;
	} break;
	case STATE::ATTACK_NORMAL:
	{
		_frameY = static_cast<int>(_direction) + 8;
	} break;
	case STATE::ATTACK_BUBBLE:
	{
		_frameY = static_cast<int>(_direction) + 8;
	} break;
	case STATE::ATTACK_BOUNCE:
	{
		_frameY = static_cast<int>(_direction) + 8;
	} break;
	}
}

void KingSlime::changeAnotherState()
{
	switch (_state)
	{
	case STATE::STOP:
	{
		changeState(STATE::WALK);
	} break;
	case STATE::WALK:
	{
		int rndState = RND->getInt(3);
		//if (rndState == 0) changeState(STATE::ATTACK_NORMAL);
		//else if (rndState == 1) changeState(STATE::ATTACK_BUBBLE);
		//else if (rndState == 2) changeState(STATE::ATTACK_BOUNCE);
		changeState(STATE::ATTACK_BUBBLE);
	} break;
	case STATE::ATTACK_NORMAL:
	{
		changeState(STATE::WALK);
	} break;
	case STATE::ATTACK_BUBBLE:
	{
		changeState(STATE::WALK);
	} break;
	case STATE::ATTACK_BOUNCE:
	{
		changeState(STATE::WALK);
	} break;
	}
}

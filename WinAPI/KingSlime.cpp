#include "Stdafx.h"
#include "KingSlime.h"

HRESULT KingSlime::init(const char * imageName, POINT position)
{
	Enemy::init(imageName, position);
	_type = ObservedType::MINION;
	
	_state = STATE::STOP;
	_direction = DIRECTION::DOWN;
	_x = position.x;
	_y = position.y;
	_frameX = _frameY = 0;
	_frameSet = 0;

	_stopSet = 8;
	_walkRndSet = RND->getFromIntTo(5, 8);
	_attackSet = 0;


	_deadForOb = false;
	_isActive = true;

	_frameDelayTime = TIMEMANAGER->getWorldTime();


	/*	이후 공격탄막 추가
	_normalBullet = new NormalBullet;
	_normalBullet->init();

	_bubbleBullet = new BubbleBullet;
	_bubbleBullet->init();

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
	switch (_state)
	{
	case STATE::STOP: cout << "STOP" << endl; break;
	case STATE::WALK: cout << "WALK" << endl; break;
	case STATE::ATTACK_BUBBLE: cout << "ATTACK_BUBBLE" << endl; break;
	case STATE::ATTACK_NORMAL: cout << "ATTACK_NORMAL" << endl; break;
	case STATE::ATTACK_BOUNCE: cout << "ATTACK_BOUNCE" << endl; break;
	}
	frameUpdate();
	move();
}

void KingSlime::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, _frameY);
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
		if (_frameSet > _walkRndSet) changeAnotherState();
	} break;
	case STATE::ATTACK_NORMAL:
	{
		if (_frameSet > _attackSet) changeAnotherState();
	} break;
	case STATE::ATTACK_BUBBLE:
	{
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
		_walkRndSet = RND->getFromIntTo(5, 10);
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
		if (rndState == 0) changeState(STATE::ATTACK_NORMAL);
		else if (rndState == 1) changeState(STATE::ATTACK_BUBBLE);
		else if (rndState == 2) changeState(STATE::ATTACK_BOUNCE);
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

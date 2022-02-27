#include "Stdafx.h"
#include "BigSlime.h"

HRESULT BigSlime::init(const char * imageName, POINT position)
{
	Enemy::init(imageName, position);

	_bossHpFrameImage = IMAGEMANAGER->addImage("BossHPBar", "Resource/Images/Lucie/CompleteImg/system/boss_Frame.bmp", 506, 32, true, RGB(255, 0, 255));
	_bossHpImage = IMAGEMANAGER->addImage("BossHPMain", "Resource/Images/Lucie/CompleteImg/system/Boss_HP_main.bmp", 485, 22, false, RGB(255, 0, 255));
	_bossHpDamageImage = IMAGEMANAGER->addImage("BossHPDamage", "Resource/Images/Lucie/CompleteImg/system/Boss_HP_damage.bmp", 485, 22, false, RGB(255, 0, 255));
	_bossHpAlpha = 0;
	_hp = _maxHP = 500;
	_hpY = 0;
	_hpWidth = _damageHpWidth = (_bossHpImage->getWidth() * (_hp / _maxHP));

	_type = ObservedType::MINION;

	_state = STATE::STOP;
	_direction = DIRECTION::DOWN;

	_alreadyShot = false;
	_angle = 0;

	_x = position.x;
	_y = position.y;
	_frameX = _frameY = 0;
	_frameSet = 0;

	_stopSet = 0;
	_walkRndSet = RND->getFromIntTo(3, 6);
	_attackSet = 0;

	_boss = false;
	_miniboss = true;
	_deadForOb = false;
	_isActive = true;

	_frameDelayTime = TIMEMANAGER->getWorldTime();


	_normalBullet = new NormalBullet;
	_normalBullet->init(100, 500);

	_bubbleBullet = new BubbleBullet;
	_bubbleBullet->init(100, 500);

	return S_OK;
}

void BigSlime::release(void)
{
	_normalBullet->release();
	_bubbleBullet->release();
	SAFE_DELETE(_normalBullet);
	SAFE_DELETE(_bubbleBullet);
	Enemy::release();
}

void BigSlime::update(void)
{
	_normalBullet->update();
	_bubbleBullet->update();
	_angle = getAngle(_x, _y, _playerPos.x, _playerPos.y);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_fixRC = RectMake(_x - 80, _y, _image->getFrameWidth() - 200, _image->getFrameHeight() - 200);
	if (!_deadForOb)
	{
		setDirection();
		frameUpdate();
		hpUpdate();
		move();
	}
	else
	{
		_deadCount++;
		if (_deadCount > 150) _isActive = false;
	}

}

void BigSlime::render(void)
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _frameX, _frameY);

	_normalBullet->render();
	_bubbleBullet->render();

	hpRender(280, 100 + _hpY);
}

STObservedData BigSlime::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_fixRC;
	temp.typeKey = &_type;
	temp.isActive = &_deadForOb;
	temp.damage = &_attack;
	return temp;
}

void BigSlime::collideObject(STObservedData obData)
{
	if (((*obData.typeKey) == ObservedType::ROCKET_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD)
		&& (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
			changeState(STATE::DEAD);
			_deadForOb = true;
		}
		else
		{
			_hp -= (*obData.damage);
		}
		(*obData.isActive) = false;
	}
}

void BigSlime::hpUpdate()
{
	_bossHpAlpha += 10;
	if (_bossHpAlpha > 255) _bossHpAlpha = 255;

	_hpWidth = (_bossHpImage->getWidth() * (_hp / _maxHP));
	if (_damageHpWidth > _hpWidth) _damageHpWidth -= (_damageHpWidth - _hpWidth) * 0.1f;
}

void BigSlime::hpRender(int x, int y)
{
	if (_bossHpAlpha <= 0) return;
	_bossHpDamageImage->alphaRender(getMemDC(), x + 7, y + 5, 0, 0, _damageHpWidth, _bossHpDamageImage->getHeight(), _bossHpAlpha);
	_bossHpImage->alphaRender(getMemDC(), x + 7, y + 5, 0, 0, _hpWidth, _bossHpImage->getHeight(), _bossHpAlpha);
	_bossHpFrameImage->alphaRender(getMemDC(), x, y, _bossHpAlpha);
}

void BigSlime::frameUpdate()
{
	if (_frameDelayTime + 0.3 < TIMEMANAGER->getWorldTime())
	{
		_frameX++;
		_frameX = _frameX % 3;
		if (_frameX == 0) _frameSet++;
		_frameDelayTime = TIMEMANAGER->getWorldTime();
	}
}

void BigSlime::setDirection()
{
	if (_angle >= 0 && _angle < 45 * PI / 180) _direction = DIRECTION::RIGHT;
	else if (_angle >= 45 * PI / 180 && _angle < 135 * PI / 180) _direction = DIRECTION::UP;
	else if (_angle >= 135 * PI / 180 && _angle < 225 * PI / 180) _direction = DIRECTION::LEFT;
	else if (_angle >= 225 * PI / 180 && _angle < 315 * PI / 180) _direction = DIRECTION::DOWN;
	else _direction = DIRECTION::RIGHT;
	changeDirectionState();
}

void BigSlime::move()
{
	switch (_state)
	{
	case STATE::STOP:
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
			for (int i = 0; i < 20; i++)
			{
				_bubbleBullet->fire(_x, _y + 80, 90 * (i / 10) * PI / 180, 3.0f, (72 * PI * 180) * i);
			}
			_alreadyShot = true;
		}
		if (_frameSet > _attackSet) changeAnotherState();
	} break;
	}
}

void BigSlime::changeState(STATE state)
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
	case STATE::DEAD: {
		_frameY = 21;
	} break;
	}
}

void BigSlime::changeDirectionState()
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
	}
}

void BigSlime::changeAnotherState()
{
	switch (_state)
	{
	case STATE::STOP:
	{
		changeState(STATE::WALK);
	} break;
	case STATE::WALK:
	{
		int rndState = RND->getInt(2);
		if (rndState == 0) changeState(STATE::ATTACK_NORMAL);
		else if (rndState == 1) changeState(STATE::ATTACK_BUBBLE);

	} break;
	case STATE::ATTACK_NORMAL:
	{
		changeState(STATE::WALK);
	} break;
	case STATE::ATTACK_BUBBLE:
	{
		changeState(STATE::WALK);
	} break;
	}
}

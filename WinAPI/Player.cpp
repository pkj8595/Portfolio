#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("Player", "Resource/Images/Lucie/CompleteImg/Player/Player.bmp", 600, 4100, 6, 41, true, RGB(255, 0, 255));

	_equipItem = new Item();
	_equipItem->_type = EITEM_TYPE::EQUIP_WEAPOEN_SWORD;

	_state = PLAYER_STATE::STOP;
	_direction = PLAYER_DIRECTION::DOWN;

	_x = CENTER_X;
	_y = CENTER_Y;

	_stateFrameCount = 0;
	_comboCooldown = 0;
	_specialAttackCooldown = 0.0f;
	_comboCount = 0;

	_hit = false;
	_hitInvTime = 0;

	_dodge = false;
	_attack = false;
	_swordSpecialAttack = false;

	_dead = false;
	
	_status._hp = _status._maxHp = 6;
	_status._speed = 2.0f;

	_frameTick = TIMEMANAGER->getWorldTime();
	_startFrame = _endFrame = 4;

	_sword = new SwordWeapon;
	_sword->init(&_x, &_y);

	_normal = new NormalWeapon;
	_normal->init(3, WINSIZE_X / 3 * 2);


	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	if (_state == PLAYER_STATE::WALK || _state == PLAYER_STATE::DODGE || _state == PLAYER_STATE::STOP)
	{
		if (_swordSpecialAttack) setDirectionByMouseInput();
		else setDirectionByKeyInput();
	}
	else setDirectionByMouseInput();
	changeState();

	setFrame();
	frameUpdate();
	
	setDodge();
	setAttack();

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_equipItem->_type = EITEM_TYPE::EQUIP_WEAPOEN_SWORD;
	}
	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_equipItem->_type = EITEM_TYPE::EMPTY;
	}
	if (!_attack || _equipItem->_type == EITEM_TYPE::EQUIP_WEAPOEN_BOW) move();


	_sword->update();
	_normal->update();

	_rc = RectMakeCenter(_x + _image->getFrameWidth() / 2, _y + _image->getFrameHeight() / 2 + 20, 25, 15);
}

void Player::render(void)
{
	Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	_image->frameRender(getMemDC(), _x, _y);
	if (_equipItem->_type == EITEM_TYPE::EQUIP_WEAPOEN_SWORD)_sword->render();
	else if (_equipItem->_type == EITEM_TYPE::EMPTY)_normal->render();
}

void Player::setFrame()
{
	int directionIndex = static_cast<int>(_direction);
	switch (_state)
	{
	case PLAYER_STATE::STOP: {
		_startFrame = _endFrame = 1 + directionIndex * 3;
		_stateFrameTick = 0.0f;
	}break;
	case PLAYER_STATE::WALK: {
		_startFrame = directionIndex*3;
		_endFrame = _startFrame + 2;
		_stateFrameTick = 0.15f;
	}break;
	case PLAYER_STATE::ATTACK_NONE: {
		_startFrame = directionIndex * 6 + 132;
		_endFrame = _startFrame + 5;
		_stateFrameTick = 0.04f;
	}break;
	case PLAYER_STATE::ATTACK_BOW: {
		_startFrame = directionIndex * 3 + 60;
		_endFrame = _startFrame + 2;
		_stateFrameTick = 0.08f;
	}break;
	case PLAYER_STATE::ATTACK_SWORD: {
		//! do Nothing		(Combo Attack)
	}break;
	case PLAYER_STATE::DODGE: {
		_startFrame = directionIndex * 6 + 84;
		_endFrame = _startFrame + 5;
		_stateFrameTick = 0.08f;
	}break;
	}
}

void Player::changeState()
{

	if (_dead)
	{
		_state = PLAYER_STATE::DEAD;
	}
	else if (_attack)
	{
		switch (_equipItem->_type)
		{
		case EITEM_TYPE::EMPTY:
		{
			_state = PLAYER_STATE::ATTACK_NONE;
		} break;
		case EITEM_TYPE::EQUIP_WEAPOEN_BOW:
		{
			_state = PLAYER_STATE::ATTACK_BOW;
		} break;
		case EITEM_TYPE::EQUIP_WEAPOEN_SWORD:
		{
			_state = PLAYER_STATE::ATTACK_SWORD;
		} break;
		}
	}
	else if (_dodge)
	{
		_state = PLAYER_STATE::DODGE;
	}
	else if (KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D') || KEYMANAGER->isStayKeyDown('W')
		|| KEYMANAGER->isStayKeyDown('S'))
	{
		_state = PLAYER_STATE::WALK;
	}
	else
	{
		_state = PLAYER_STATE::STOP;
	}
}

void Player::setDirectionByKeyInput()
{
	if (_dodge) return;
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (KEYMANAGER->isStayKeyDown('S')) _direction = PLAYER_DIRECTION::LEFTDOWN;
		else if (KEYMANAGER->isStayKeyDown('W')) _direction = PLAYER_DIRECTION::LEFTUP;
		else _direction = PLAYER_DIRECTION::LEFT;
	}
	else if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown('S')) _direction = PLAYER_DIRECTION::RIGHTDOWN;
		else if (KEYMANAGER->isStayKeyDown('W')) _direction = PLAYER_DIRECTION::RIGHTUP;
		else _direction = PLAYER_DIRECTION::RIGHT;
	}
	else if (KEYMANAGER->isStayKeyDown('W'))
	{
		_direction = PLAYER_DIRECTION::UP;
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		 _direction = PLAYER_DIRECTION::DOWN;
	}
}

void Player::setDirectionByMouseInput()
{
	float angle = MY_UTIL::getAngle(_x, _y, _ptMouse.x, _ptMouse.y) * 180 / PI;
	if ((angle >= 0 && angle < 22.5) || (angle >= 337.5 && angle < 360)) _direction = PLAYER_DIRECTION::RIGHT;
	else if (angle >= 22.5 && angle < 67.5) _direction = PLAYER_DIRECTION::RIGHTUP;
	else if (angle >= 67.5 && angle < 112.5) _direction = PLAYER_DIRECTION::UP;
	else if (angle >= 112.5 && angle < 157.5) _direction = PLAYER_DIRECTION::LEFTUP;
	else if (angle >= 157.5 && angle < 202.5) _direction = PLAYER_DIRECTION::LEFT;
	else if (angle >= 202.5 && angle < 247.5) _direction = PLAYER_DIRECTION::LEFTDOWN;
	else if (angle >= 247.5 && angle < 292.5) _direction = PLAYER_DIRECTION::DOWN;
	else if (angle >= 292.5 && angle < 337.5) _direction = PLAYER_DIRECTION::RIGHTDOWN;
}

void Player::frameUpdate()
{
	if (_currentFrame < _startFrame || _currentFrame > _endFrame) _currentFrame = _startFrame;
	if (_stateFrameTick + _frameTick <= TIMEMANAGER->getWorldTime())
	{
		_frameTick = TIMEMANAGER->getWorldTime();
		
		_image->setFrameX(_currentFrame % 6);
		_image->setFrameY(_currentFrame /6);
		if (_currentFrame >= _endFrame) _currentFrame = _startFrame;
		else _currentFrame++;
	}
}

void Player::setDodge()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !_dodge && !_attack)
	{
		_dodge = true;
	}
	if (_state == PLAYER_STATE::DODGE && _currentFrame >= _endFrame)
	{
		_dodge = false;
	}
}

void Player::setAttack()
{
	if (_dodge && _equipItem->_type != EITEM_TYPE::EQUIP_WEAPOEN_SWORD) return;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_attack)
		{
			_attack = true;
			if (_equipItem->_type == EITEM_TYPE::EMPTY)
			{
				float angle = MY_UTIL::getAngle(_x, _y, _ptMouse.x, _ptMouse.y);
				_normal->fire(_x + 50, _y + 50, angle);
			}
			else if (_equipItem->_type == EITEM_TYPE::EQUIP_WEAPOEN_BOW)
			{

			}
			if (_dodge)
			{
				_dodge = false;
				setSwordSpecialAttack();
			}
			else if (_equipItem->_type == EITEM_TYPE::EQUIP_WEAPOEN_SWORD)
			{
				_startFrame = static_cast<int>(_direction) * 8 + 180;
				_endFrame = _startFrame + 1;
				_stateFrameTick = 0.15f;
				_comboCooldown = TIMEMANAGER->getWorldTime();
				_comboCount = 0;
				_sword->fire(0, static_cast<int>(_direction));
			}
		}
		else
		{
			setSwordAttack();
		}
		
	}
	if (_comboCooldown <= TIMEMANAGER->getWorldTime() - 0.35f && _equipItem->_type == EITEM_TYPE::EQUIP_WEAPOEN_SWORD)
	{
		_attack = false;
	}
	if (_specialAttackCooldown <= TIMEMANAGER->getWorldTime() - 0.1f && _swordSpecialAttack)
	{
		_swordSpecialAttack = false;
	}
	if (_state == PLAYER_STATE::ATTACK_BOW && _currentFrame >= _endFrame)
	{
		_attack = false;
	}
	else if (_state == PLAYER_STATE::ATTACK_NONE && _currentFrame >= _endFrame)
	{
		_attack = false;
	}
}

void Player::setSwordAttack()
{
	if (!_attack || _state != PLAYER_STATE::ATTACK_SWORD) return;				
	if (_comboCooldown <= TIMEMANAGER->getWorldTime() - 0.2f) return;	//공격 사이 딜레이 쿨타임
	if (_comboCount >= 4) return;
	switch (_comboCount)
	{
	case 0: {
		_comboCooldown = TIMEMANAGER->getWorldTime();
		_startFrame = _currentFrame = static_cast<int>(_direction) * 8 + 182;
		_endFrame = _startFrame + 2;
		_stateFrameTick = 0.08f;
		_comboCount++;
		_sword->fire(1, static_cast<int>(_direction));
	}break;
	case 1: {
		_comboCooldown = TIMEMANAGER->getWorldTime();
		_startFrame = _currentFrame = static_cast<int>(_direction) * 8 + 180;
		_endFrame = _startFrame + 1;
		_stateFrameTick = 0.08f;
		_comboCount++;
		_sword->fire(2, static_cast<int>(_direction));
	}break;
	case 2: {
		_comboCooldown = TIMEMANAGER->getWorldTime();
		_startFrame = _currentFrame = static_cast<int>(_direction) * 8 + 182;
		_endFrame = _startFrame + 2;
		_stateFrameTick = 0.08f;
		_comboCount++;
		_sword->fire(3, static_cast<int>(_direction));
	}break;
	case 3: {
		_comboCooldown = TIMEMANAGER->getWorldTime();
		_startFrame = _currentFrame = static_cast<int>(_direction) * 8 + 185;
		_endFrame = _startFrame + 2;
		_stateFrameTick = 0.08f;
		_comboCount++;
		_sword->fire(4, static_cast<int>(_direction));
	}break;
	default: break;
	}
}

void Player::setSwordSpecialAttack()
{
	//대쉬중 공격(돌진)
	setDirectionByMouseInput();
	_specialAttackCooldown = TIMEMANAGER->getWorldTime();
	_sword->fire(4, static_cast<int>(_direction));
	_swordSpecialAttack = true;
}


void Player::move()
{
	if (_state != PLAYER_STATE::WALK && _state != PLAYER_STATE::DODGE && _state != PLAYER_STATE::ATTACK_BOW) return;
	switch (_direction)
	{
	case PLAYER_DIRECTION::LEFT: 
	{
		if (_swordSpecialAttack)
		{
			_x -= 12.0f;
		}
		else if (_state == PLAYER_STATE::DODGE)
		{
			_x -= 4.0f;
		}
		else
		{
			_x -= _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::RIGHT:
	{
		if (_swordSpecialAttack)
		{
			_x += 12.0f;
		}
		else if (_state == PLAYER_STATE::DODGE)
		{
			_x += 4.0f;
		}
		else
		{
			_x += _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::UP:
	{
		if (_swordSpecialAttack)
		{
			_y -= 12.0f;
		}
		else if (_state == PLAYER_STATE::DODGE)
		{
			_y -= 4.0f;
		}
		else
		{
			_y -= _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::DOWN:
	{
		if (_swordSpecialAttack)
		{
			_y += 12.0f;
		}
		else if (_state == PLAYER_STATE::DODGE)
		{
			_y += 4.0f;
		}
		else
		{
			_y += _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::LEFTUP:
	{
		if (_swordSpecialAttack)
		{
			_x -= 12.0f;
			_y -= 12.0f;
		}
		else if (_state == PLAYER_STATE::DODGE)
		{
			_x -= 4.0f;
			_y -= 4.0f;
		}
		else
		{
			_x -= _status._speed;
			_y -= _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::RIGHTUP:
	{
		if (_swordSpecialAttack)
		{
			_x += 12.0f;
			_y -= 12.0f;
		}
		else if (_state == PLAYER_STATE::DODGE)
		{
			_x += 4.0f;
			_y -= 4.0f;
		}
		else
		{
			_x += _status._speed;
			_y -= _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::LEFTDOWN:
	{
		if (_swordSpecialAttack)
		{
			_x -= 12.0f;
			_y += 12.0f;
		}
		else if (_state == PLAYER_STATE::DODGE)
		{
			_x -= 4.0f;
			_y += 4.0f;
		}
		else
		{
			_x -= _status._speed;
			_y += _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::RIGHTDOWN:
	{
		if (_swordSpecialAttack)
		{
			_x += 12.0f;
			_y += 12.0f;
		}
		else if (_state == PLAYER_STATE::DODGE)
		{
			_x += 4.0f;
			_y += 4.0f;
		}
		else
		{
			_x += _status._speed;
			_y += _status._speed;
		}
	} break;
	}
}

void Player::setCollision()
{
	switch (_direction)
	{
	case PLAYER_DIRECTION::DOWN : {
		if (_swordSpecialAttack) _y -= 12.0f;
		else if (_dodge) _y -= 4.0f;
		else _y -= _status._speed;
	} break;
	case PLAYER_DIRECTION::UP: {
		if (_swordSpecialAttack) _y += 12.0f;
		else if (_dodge) _y += 4.0f;
		else _y += _status._speed;
	} break;
	case PLAYER_DIRECTION::LEFT: {
		if (_swordSpecialAttack) _x += 12.0f;
		else if (_dodge) _x += 4.0f;
		else _x += _status._speed;
	} break;
	case PLAYER_DIRECTION::RIGHT: {
		if (_swordSpecialAttack) _x -= 12.0f;
		else if (_dodge) _x -= 4.0f;
		else _x -= _status._speed;
	} break;
	case PLAYER_DIRECTION::LEFTDOWN: {
		if (_swordSpecialAttack)
		{
			_x += 12.0f;
			_y -= 12.0f;
		}
		else if (_dodge)
		{
			_x += 4.0f;
			_y -= 4.0f;
		}
		else
		{
			_x += _status._speed;
			_y -= _status._speed;
		}	
	} break;
	case PLAYER_DIRECTION::RIGHTDOWN: {
		if (_swordSpecialAttack)
		{
			_x -= 12.0f;
			_y -= 12.0f;
		}
		else if (_dodge)
		{
			_x -= 4.0f;
			_y -= 4.0f;
		}
		else
		{
			_x -= _status._speed;
			_y -= _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::LEFTUP: {
		if (_swordSpecialAttack)
		{
			_x += 12.0f;
			_y += 12.0f;
		}
		else if (_dodge)
		{
			_x += 4.0f;
			_y += 4.0f;
		}
		else
		{
			_x += _status._speed;
			_y += _status._speed;
		}
	} break;
	case PLAYER_DIRECTION::RIGHTUP: {
		if (_swordSpecialAttack)
		{
			_x -= 12.0f;
			_y += 12.0f;
		}
		else if (_dodge)
		{
			_x -= 4.0f;
			_y += 4.0f;
		}
		else
		{
			_x -= _status._speed;
			_y += _status._speed;
		}
	} break;
	}
}

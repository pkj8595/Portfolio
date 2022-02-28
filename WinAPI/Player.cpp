#include "Stdafx.h"
#include "Player.h"


HRESULT Player::init(void)
{
	RECTOBSERVERMANAGER->registerObserved(this);
	_type = ObservedType::ROCKET;
	_image = IMAGEMANAGER->addFrameImage("Player", "Resource/Images/Lucie/CompleteImg/Player/Player.bmp", 600, 4100, 6, 41, true, RGB(255, 0, 255));
	_swordStackImage = IMAGEMANAGER->addImage("SwordStack", "Resource/Images/Lucie/CompleteImg/system/ruby.bmp", 13, 14, true, RGB(255, 0, 255));
	_bowStackImage = IMAGEMANAGER->addImage("BowStack", "Resource/Images/Lucie/CompleteImg/system/emerald.bmp", 16, 13, true, RGB(255, 0, 255));
	_hitBG = IMAGEMANAGER->addImage("HitEffect", "Resource/Images/Lucie/CompleteImg/effect/hitScreen.bmp", 1104, 960, true, RGB(255, 0, 255));
	_dodgeBG = IMAGEMANAGER->addImage("DodgeEffect", "Resource/Images/Lucie/CompleteImg/effect/whiteScreen.bmp", 1104, 960, true, RGB(255, 0, 255));

	_state = PLAYER_STATE::STOP;
	_level = 1;
	_hitAlpha = 0;
	_dodgeAlpha = 0;
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

	_isTextShow = false;
	_dead = false;
	
	_swordStack = 0;
	_bowStack = 0;
	_alreadyAddBowStack = false;
	_tripleshot = false;
	_tripleShotStartCount = 0.0f;

	_status._hp = _status._maxHp = 6;
	_status._mana = _status._maxMana = 3;
	_status._critical = 10.0f;
	_status._offencePower = 10.0f;
	_status._magicPower = 10.0f;
	_status._speed = 2.0f;
	//_status._speed = 8.0f;
	_status._damageBalance = 0.0f;
	_status._experience = 0.0f;
	_status._maxExperience = 100.0f;
	_status._stamina = _status._maxStamina = 100.0f;
	_totalStatus = _status;
	


	_frameTick = TIMEMANAGER->getWorldTime();
	_startFrame = _endFrame = 4;

	_sword = new SwordWeapon;
	_sword->init(&_x, &_y);

	_normal = new NormalWeapon;
	_normal->init(5, WINSIZE_X / 3 * 2);

	_bow = new BowWeapon;
	_bow->init(15, WINSIZE_X / 3 * 2);

	_statusUI = new PlayerStatusUI;
	_statusUI->init(&_totalStatus, &_level);

	_inventory = new Inventory;
	_inventory->init();
	_inventory->setPTotalattribute(&_totalStatus);
	_inventory->setPlayerAttribute(&_status);

	_efm = new EffectManager;
	_efm->init();

	_equipItem = _inventory->getEquipWeapon();
	
	return S_OK;
}

void Player::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
	_inventory->release();
}

void Player::update(void)
{
	if (_state == PLAYER_STATE::WALK || _state == PLAYER_STATE::DODGE || _state == PLAYER_STATE::STOP)
	{
		if (_swordSpecialAttack) setDirectionByMouseInput();
		else if (_bow->isFiring()) setDirectionByMouseInput();
		else setDirectionByKeyInput();
	}
	else setDirectionByMouseInput();

	changeState();

	setFrame();
	frameUpdate();
	
	setDodge();

	if (!_inventory->getIsShowInven()) { setAttack(); }

	checkBowStack();

	healStamina();

	if (!_attack || (*_equipItem)->_type == EITEM_TYPE::EQUIP_WEAPON_BOW)
	{	
		if (!_isTextShow)
		{
			move();
		}
	}
	computeTotalAttribute(); // 합산
	_sword->update();
	_normal->update();
	_bow->update();
	_statusUI->update();
	_inventory->update(); 
	_efm->update();

	_rc = RectMakeCenter(_x + _image->getFrameWidth() / 2, _y + _image->getFrameHeight() / 2 + 20, 8, 5);

	if (_hit) _hitInvTime--;
	if (_hitInvTime <= 0) _hit = false;
	if (_state != PLAYER_STATE::DODGE) _alreadyAddBowStack = false;
	if (_hitAlpha > 0) _hitAlpha -= 16;
	if (_dodgeAlpha > 0) _dodgeAlpha -= 16;

	setLevelUp();
}

void Player::render(void)
{
	_image->frameRender(getMemDC(), _x, _y);
	_efm->render();
	//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}
void Player::showSwordStack()
{
	int fixX;
	int fixY = 75;
	switch (_swordStack)
	{
	case 0: fixX = 44; break;
	case 1: fixX = 44; break;
	case 2: fixX = 37; break;
	case 3: fixX = 30; break;
	}
	for (int i = 0; i < _swordStack; i++)
	{
		_swordStackImage->render(getMemDC(), _x + fixX + i*14, _y + fixY);
	}

}

void Player::showBowStack()
{
	int fixX;
	int fixY = 75;
	switch (_bowStack)
	{
	case 0: fixX = 42; break;
	case 1: fixX = 42; break;
	case 2: fixX = 36; break;
	case 3: fixX = 28; break;
	case 4: fixX = 36; break;
	case 5: fixX = 28; break;
	default: fixX = 42; break;
	}
	if (_bowStack <= 3)
	{
		for (int i = 0; i < _bowStack; i++)
		{
			_bowStackImage->render(getMemDC(), _x + fixX + i * 15, _y + fixY);
		}
	}
	else if (_bowStack == 4)
	{
		for (int i = 0; i < 2; i++)
		{
			_bowStackImage->render(getMemDC(), _x + fixX + i * 15, _y + fixY);
			_bowStackImage->render(getMemDC(), _x + fixX + i * 15, _y + fixY + 15);
		}
	}
	else if (_bowStack == 5)
	{
		for (int i = 0; i < 3; i++)
		{
			_bowStackImage->render(getMemDC(), _x + fixX + i * 15, _y + fixY);
		}
		
		for (int i = 0; i < 2; i++)
		{
			_bowStackImage->render(getMemDC(), _x + fixX + 8 + i * 15, _y + fixY + 15);
		}
	}
	else return;
}

void Player::checkBowStack()
{
	if (_bowStack != 5) return;
	else
	{
		if (!_tripleshot)
		{
			_tripleshot = true;
			_tripleShotStartCount = TIMEMANAGER->getWorldTime();
		}
		else
		{
			if (_tripleShotStartCount <= TIMEMANAGER->getWorldTime() - 5.0f)
			{
				_tripleshot = false;
				_bowStack = 0;
			}
		}
	}
}

STObservedData Player::getRectUpdate()
{
	STObservedData temp;

	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_attack;
	return temp;
}


void Player::collideObject(STObservedData obData)
{
	//아이템 획득
	if (*obData.typeKey == ObservedType::ITEM)
	{
		//*obData.isActive -> item -> isCollider
		if (*obData.isActive)
		{
			//*obData.angle -> item -> respoenseTime
			if (TIMEMANAGER->getWorldTime() > *obData.angle + 1.0f)
			{
				_inventory->pushItem(*obData.number);
			}
		}
	} 
	else
	{
		if (_swordSpecialAttack) return;
		if (_state == PLAYER_STATE::DODGE)
		{
			if (_totalStatus._mana < _totalStatus._maxMana) _status._mana++;
			if ((*_equipItem)->_type == EITEM_TYPE::EQUIP_WEAPON_BOW)
			{
				if (_bowStack < 5 && !_tripleshot && !_alreadyAddBowStack)
				{

					_bowStack++;

				}
			}
			if (!_alreadyAddBowStack) _dodgeAlpha = 80;
			_alreadyAddBowStack = true;
		}
		else if (!_hit)
		{
			_hitAlpha = 255;
			_status._hp -= 1;
			_hit = true;
			_hitInvTime = 100;
		}
	}

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
		switch ((*_equipItem)->_type)
		{
		case EITEM_TYPE::EMPTY:
		{
			_state = PLAYER_STATE::ATTACK_NONE;
		} break;
		case EITEM_TYPE::EQUIP_WEAPON_BOW:
		{
			_state = PLAYER_STATE::ATTACK_BOW;
		} break;
		case EITEM_TYPE::EQUIP_WEAPON_SWORD:
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
		if (_status._stamina >= 10.0f)
		{
			_dodge = true;
			_status._stamina -= 10.0f;
		}

	}
	if (_state == PLAYER_STATE::DODGE && _currentFrame >= _endFrame)
	{
		_dodge = false;
	}
}

void Player::setAttack()
{
	if (_dodge && (*_equipItem)->_type != EITEM_TYPE::EQUIP_WEAPON_SWORD) return;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (!_attack)
		{
			if (_status._stamina < 5.0f) return;
			_attack = true;
			if ((*_equipItem)->_type == EITEM_TYPE::EMPTY)
			{
				if (_attackCount < TIMEMANAGER->getWorldTime() - 0.3f)
				{
					float angle = MY_UTIL::getAngle(_x, _y, _ptMouse.x, _ptMouse.y);
					_normal->fire(calculatePhysicalDamage(), _x + 50, _y + 50, angle);
					_status._stamina -= 5.0f;
					_attackCount = TIMEMANAGER->getWorldTime();
				}
			}
			else if ((*_equipItem)->_type == EITEM_TYPE::EQUIP_WEAPON_BOW)
			{
				if (_attackCount < TIMEMANAGER->getWorldTime() - 0.3f)
				{
					float angle = MY_UTIL::getAngle(_x, _y, _ptMouse.x, _ptMouse.y);
					if (_tripleshot)
					{
						_bow->fire(calculatePhysicalDamage(), _x + 50, _y + 50, angle - 15 * PI / 180);
						_bow->fire(calculatePhysicalDamage(), _x + 50, _y + 50, angle);
						_bow->fire(calculatePhysicalDamage(), _x + 50, _y + 50, angle + 15 * PI / 180);
					}
					else
					{
						_bow->fire(calculatePhysicalDamage(), _x + 50, _y + 50, angle);
					}
					_status._stamina -= 5.0f;
					_attackCount = TIMEMANAGER->getWorldTime();
				}
			}
			if (_dodge)
			{
				_dodge = false;
				setSwordSpecialAttack();
				_status._stamina -= 5.0f;
			}
			else if ((*_equipItem)->_type == EITEM_TYPE::EQUIP_WEAPON_SWORD)
			{
				_startFrame = static_cast<int>(_direction) * 8 + 180;
				_endFrame = _startFrame + 1;
				_stateFrameTick = 0.15f;
				_comboCooldown = TIMEMANAGER->getWorldTime();
				_comboCount = 0;
				_sword->fire(calculatePhysicalDamage(), 0, static_cast<int>(_direction));
				_status._stamina -= 5.0f;
			}
		}
		else
		{
			if (_totalStatus._stamina < 5.0f) return;
			setSwordAttack();
		}
	}
	if (_comboCooldown <= TIMEMANAGER->getWorldTime() - 0.35f && (*_equipItem)->_type == EITEM_TYPE::EQUIP_WEAPON_SWORD)
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
		_sword->fire(calculatePhysicalDamage(), 1, static_cast<int>(_direction));
	}break;
	case 1: {
		_comboCooldown = TIMEMANAGER->getWorldTime();
		_startFrame = _currentFrame = static_cast<int>(_direction) * 8 + 180;
		_endFrame = _startFrame + 1;
		_stateFrameTick = 0.08f;
		_comboCount++;
		_sword->fire(calculatePhysicalDamage(), 2, static_cast<int>(_direction));
		_status._stamina -= 5.0f;
	}break;
	case 2: {
		_comboCooldown = TIMEMANAGER->getWorldTime();
		_startFrame = _currentFrame = static_cast<int>(_direction) * 8 + 182;
		_endFrame = _startFrame + 2;
		_stateFrameTick = 0.08f;
		_comboCount++;
		_sword->fire(calculatePhysicalDamage(), 3, static_cast<int>(_direction));
	}break;
	case 3: {
		_comboCooldown = TIMEMANAGER->getWorldTime();
		_startFrame = _currentFrame = static_cast<int>(_direction) * 8 + 185;
		_endFrame = _startFrame + 2;
		_stateFrameTick = 0.08f;
		_comboCount++;
		_sword->fire(calculatePhysicalDamage(), 4, static_cast<int>(_direction));
		_status._stamina -= 5.0f;
		if(_swordStack < 3) _swordStack++;
	}break;
	default: break;
	}
}

void Player::setSwordSpecialAttack()
{
	//대쉬중 공격(돌진)
	setDirectionByMouseInput();
	_specialAttackCooldown = TIMEMANAGER->getWorldTime();
	_sword->fire(calculatePhysicalDamage() * (1 + 0.5 *_swordStack), 4, static_cast<int>(_direction));
	_swordSpecialAttack = true;
	_swordStack = 0;
}



void Player::move()
{
	
	if (_state != PLAYER_STATE::WALK && _state != PLAYER_STATE::DODGE && _state != PLAYER_STATE::ATTACK_BOW) return;
	if (_state == PLAYER_STATE::ATTACK_BOW)
	{	
		setDirectionByKeyInput();
	}
	else if (_bow->isFiring()) setDirectionByKeyInput();
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
			_x -= _totalStatus._speed;
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
			_x += _totalStatus._speed;
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
			_y -= _totalStatus._speed;
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
			_y += _totalStatus._speed;
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
			_x -= _totalStatus._speed;
			_y -= _totalStatus._speed;
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
			_x += _totalStatus._speed;
			_y -= _totalStatus._speed;
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
			_x -= _totalStatus._speed;
			_y += _totalStatus._speed;
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
			_x += _totalStatus._speed;
			_y += _totalStatus._speed;
		}
	} break;
	}
}

void Player::healStamina()
{
	if (_status._stamina < _totalStatus._maxStamina && _state != PLAYER_STATE::DODGE && _state != PLAYER_STATE::ATTACK_BOW
		&& _state != PLAYER_STATE::ATTACK_NONE && _state != PLAYER_STATE::ATTACK_SWORD)
	{
		_status._stamina += 0.4f;
	}
	else if (_status._stamina > _totalStatus._maxStamina) 
	{
		_status._stamina = _totalStatus._maxStamina; 
	}
}

void Player::setCollision()
{
	switch (_direction)
	{
	case PLAYER_DIRECTION::DOWN : {
		if (_swordSpecialAttack) _y -= 12.0f;
		else if (_dodge) _y -= 4.0f;
		else _y -= _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::UP: {
		if (_swordSpecialAttack) _y += 12.0f;
		else if (_dodge) _y += 4.0f;
		else _y += _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::LEFT: {
		if (_swordSpecialAttack) _x += 12.0f;
		else if (_dodge) _x += 4.0f;
		else _x += _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::RIGHT: {
		if (_swordSpecialAttack) _x -= 12.0f;
		else if (_dodge) _x -= 4.0f;
		else _x -= _totalStatus._speed;
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
			_x += _totalStatus._speed;
			_y -= _totalStatus._speed;
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
			_x -= _totalStatus._speed;
			_y -= _totalStatus._speed;
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
			_x += _totalStatus._speed;
			_y += _totalStatus._speed;
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
			_x -= _totalStatus._speed;
			_y += _totalStatus._speed;
		}
	} break;
	}
}

void Player::computeTotalAttribute()
{
	_totalStatus = _status + _inventory->getItemTotalAttribute();
	if (_totalStatus._maxHp < _status._hp)
	{
		_status._hp = _totalStatus._maxHp;
	}
	if (_totalStatus._maxMana < _status._mana)
	{
		_status._mana = _totalStatus._maxMana;
	}
}

float Player::calculatePhysicalDamage()
{ 
	float minDamage = _totalStatus._offencePower - ((_totalStatus._offencePower * 0.3f) * (1.0f - _totalStatus._damageBalance*0.01));
	float maxDamage = _totalStatus._offencePower;
	if (minDamage > maxDamage) minDamage = maxDamage;
	float criticalProperty = _totalStatus._critical * 0.01;
	if (criticalProperty > 1.0f) criticalProperty = 1.0f;
	
	float rndDamage = RND->getFromFloatTo(minDamage, maxDamage);
	float rndCritical = RND->getFromFloatTo(0.0f, 1.0f);
	if (rndCritical <= criticalProperty) rndDamage *= 2; 
	return rndDamage;
}

float Player::calculateMagicDamage()
{
	float minDamage = _totalStatus._magicPower - ((_totalStatus._magicPower * 0.3f) * (1.0f - _totalStatus._damageBalance*0.01));
	float maxDamage = _totalStatus._magicPower;
	if (minDamage > maxDamage) minDamage = maxDamage;
	float criticalProperty = _totalStatus._critical * 0.01;
	if (criticalProperty > 1.0f) criticalProperty = 1.0f;

	float rndDamage = RND->getFromFloatTo(minDamage, maxDamage);
	float rndCritical = RND->getFromFloatTo(0.0f, 1.0f);
	
	if (rndDamage <= criticalProperty) rndDamage *= 2;
	return rndDamage;
}

void Player::setLevelUp()
{
	if (_status._experience >= _totalStatus._maxExperience)
	{
		_level++;
		_status._experience -= _totalStatus._maxExperience;
		_status._maxExperience *= 1.3f;
		_status._offencePower += 1.0f;
		_efm->createEffect("Levelup", _rc);
	}
}
void Player::printHitBG()
{
	if (_hitAlpha > 0) _hitBG->alphaRender(getMemDC(), _hitAlpha);
	if (_dodgeAlpha > 0) _dodgeBG->alphaRender(getMemDC(), _dodgeAlpha);
}
void Player::printStack()
{
	if ((*_equipItem)->_type == EITEM_TYPE::EQUIP_WEAPON_SWORD)
	{
		showSwordStack();
		_sword->render();
	}
	else if ((*_equipItem)->_type == EITEM_TYPE::EMPTY)_normal->render();

	else if ((*_equipItem)->_type == EITEM_TYPE::EQUIP_WEAPON_BOW)
	{
		showBowStack();
		_bow->render();
	}
}

void Player::printInventory()
{
	_inventory->render();
}

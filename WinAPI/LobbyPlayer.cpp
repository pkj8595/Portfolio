#include "Stdafx.h"
#include "LobbyPlayer.h"

#include "Stdafx.h"
#include "Player.h"


HRESULT LobbyPlayer::init(void)
{
	_type = ObservedType::ROCKET;
	_image = IMAGEMANAGER->addFrameImage("Player", "Resource/Images/Lucie/CompleteImg/Player/Player.bmp", 600, 4100, 6, 41, true, RGB(255, 0, 255));

	_state = PLAYER_STATE::STOP;
	_level = 1;
	_direction = PLAYER_DIRECTION::DOWN;

	_x = CENTER_X;
	_y = CENTER_Y;

	_stateFrameCount = 0;

	_isTextShow = false;
	_dead = false;

	_status._hp = _status._maxHp = 6;
	_status._mana = _status._maxMana = 3;
	_status._critical = 10.0f;
	_status._offencePower = 10.0f;
	_status._magicPower = 10.0f;
	_status._speed = 2.0f;
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

	_tsm = new TextSystemManager;
	_tsm->init();
	_tsm->iscollBox = false;

	_inventory = new Inventory;
	_inventory->init();
	_inventory->setPTotalattribute(&_totalStatus);
	_inventory->setPlayerAttribute(&_status);


	_equipItem = _inventory->getEquipWeapon();

	return S_OK;
}

void LobbyPlayer::release(void)
{
	_inventory->release();
	_tsm->release();
}

void LobbyPlayer::update(void)
{

	if (_state == PLAYER_STATE::WALK || _state == PLAYER_STATE::STOP)
	{
		setDirectionByKeyInput();
	}
	else setDirectionByMouseInput();

	changeState();

	setFrame();
	frameUpdate();

	healStamina();

	_tsm->update();
	if (!_isTextShow)
	{
		move();
	}
	computeTotalAttribute(); // гу╩Й
	_sword->update();
	_normal->update();
	_bow->update();
	_statusUI->update();
	_inventory->update();

	_rc = RectMakeCenter(_x + _image->getFrameWidth() / 2, _y + _image->getFrameHeight() / 2 + 20, 8, 5);

}

void LobbyPlayer::render(void)
{
	_image->frameRender(getMemDC(), _x, _y);
	_inventory->render();
}

STObservedData LobbyPlayer::getRectUpdate()
{
	STObservedData temp;

	temp.rc = &_rc;
	temp.typeKey = &_type;
	return temp;
}

void LobbyPlayer::setFrame()
{
	int directionIndex = static_cast<int>(_direction);
	switch (_state)
	{
	case PLAYER_STATE::STOP: {
		_startFrame = _endFrame = 1 + directionIndex * 3;
		_stateFrameTick = 0.0f;
	}break;
	case PLAYER_STATE::WALK: {
		_startFrame = directionIndex * 3;
		_endFrame = _startFrame + 2;
		_stateFrameTick = 0.15f;
	}break;
	}
}

void LobbyPlayer::changeState()
{

	if (_dead)
	{
		_state = PLAYER_STATE::DEAD;
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

void LobbyPlayer::setDirectionByKeyInput()
{
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

void LobbyPlayer::setDirectionByMouseInput()
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

void LobbyPlayer::frameUpdate()
{
	if (_currentFrame < _startFrame || _currentFrame > _endFrame) _currentFrame = _startFrame;
	if (_stateFrameTick + _frameTick <= TIMEMANAGER->getWorldTime())
	{
		_frameTick = TIMEMANAGER->getWorldTime();

		_image->setFrameX(_currentFrame % 6);
		_image->setFrameY(_currentFrame / 6);
		if (_currentFrame >= _endFrame) _currentFrame = _startFrame;
		else _currentFrame++;
	}
}

void LobbyPlayer::move()
{

	if (_state != PLAYER_STATE::WALK) return;
	else if (_bow->isFiring()) setDirectionByKeyInput();
	switch (_direction)
	{
	case PLAYER_DIRECTION::LEFT:
	{
		_x -= _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::RIGHT:
	{
		_x += _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::UP:
	{
		_y -= _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::DOWN:
	{
		_y += _totalStatus._speed;

	} break;
	case PLAYER_DIRECTION::LEFTUP:
	{
		_x -= _totalStatus._speed;
		_y -= _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::RIGHTUP:
	{
		_x += _totalStatus._speed;
		_y -= _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::LEFTDOWN:
	{
		_x -= _totalStatus._speed;
		_y += _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::RIGHTDOWN:
	{
		_x += _totalStatus._speed;
		_y += _totalStatus._speed;
	} break;
	}
}

void LobbyPlayer::healStamina()
{
	if (_status._stamina < _totalStatus._maxStamina)
	{
		_status._stamina += 0.4f;
	}
}

void LobbyPlayer::checkLevelUp()
{
	if (_status._experience >= _totalStatus._maxExperience)
	{
		_status._experience = 0;
		_totalStatus._maxExperience *= 1.1f;

	}
}

void LobbyPlayer::setCollision()
{
	switch (_direction)
	{
	case PLAYER_DIRECTION::DOWN: {
		_y -= _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::UP: {
		_y += _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::LEFT: {
		_x += _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::RIGHT: {
		_x -= _totalStatus._speed;
	} break;
	case PLAYER_DIRECTION::LEFTDOWN: {
		{
			_x += _totalStatus._speed;
			_y -= _totalStatus._speed;
		}
	} break;
	case PLAYER_DIRECTION::RIGHTDOWN: {
		{
			_x -= _totalStatus._speed;
			_y -= _totalStatus._speed;
		}
	} break;
	case PLAYER_DIRECTION::LEFTUP: {
		{
			_x += _totalStatus._speed;
			_y += _totalStatus._speed;
		}
	} break;
	case PLAYER_DIRECTION::RIGHTUP: {
		{
			_x -= _totalStatus._speed;
			_y += _totalStatus._speed;
		}
	} break;
	}
}

void LobbyPlayer::computeTotalAttribute()
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

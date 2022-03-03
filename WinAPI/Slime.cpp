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
	_type = ObservedType::MINION;
	_x = position.x;
	_y = position.y;
	_randomX = 0;
	_randomY = 0;
	_speed = 0.5f;
	_frameSpeed = 0.3f;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_randomTimeCount = RND->getFromFloatTo(0.f,2.f);
	_moveWorldTime = TIMEMANAGER->getWorldTime();
	_attacWorldTime = TIMEMANAGER->getWorldTime();
	_playerDistance = 0.0f;
	_range = 300.f;
	_moveCheck = true;
	_attackRange = 150;
	_deadForOb = false;
	_deadTimeCount = TIMEMANAGER->getWorldTime() + 9999.999f;
	_circleBullet = new CircleMissile;
	_circleBullet->init(10, 300);
	_threeDirectionBullet = new ThreeDirectionMissile;
	_threeDirectionBullet->init(3, 300);
	_hp = 100.0f;
	_exp = 30.0f;

	_direction = SLIMEDIRECTION::SL_DOWN;
	_state = SLIMESTATE::SL_IDLE;

	return S_OK;
}

void Slime::release(void)
{
	_circleBullet->release();
	_threeDirectionBullet->release();
	SAFE_DELETE(_circleBullet);
	SAFE_DELETE(_threeDirectionBullet);
	Enemy::release();
}

void Slime::update(void)
{
	Enemy::update();
	_circleBullet->update();
	_threeDirectionBullet->update();

	//�÷��̾� ���� ������ ������ ���
	if (_deadTimeCount < TIMEMANAGER->getWorldTime() - 0.5f)
	{
		//_frameY = 1;
		_state = SLIMESTATE::SL_IDLE;
		_isActive = false;
	}
	if (_state == SLIMESTATE::SL_DEAD)
	{
		if (_currentFrameX >= _image->getMaxFrameX())
		{
			_deadTimeCount = TIMEMANAGER->getWorldTime();
		}
	}
	else if (playerCheck())
	{
		if (_moveCheck)
			pursuePlayer();

		//���� ��Ÿ� ������ ������ ���
		if (_playerDistance < _attackRange)
		{
			attackParttern();
		}
	}
	else
	{
		_moveCheck = true;
		//���� ��ǥ ����
		randomPosCreate();
	}


	_rc = RectMakeCenter(_x + _image->getFrameWidth()/2, _y+_image->getFrameHeight()/2 + 20, _image->getFrameWidth() / 2, _image->getFrameHeight() / 2);

}

void Slime::render(void)
{
	//Enemy::render();
	if (_isActive)
	{
		frame();
		draw();
	}
}

void Slime::move(void)
{

}

void Slime::draw(void)
{
	animation();
	_image->frameRender(getMemDC(),
		_x - CAMERAMANAGER->getCameraRect().left,
		_y - CAMERAMANAGER->getCameraRect().top,
		_currentFrameX, _currentFrameY);
	_threeDirectionBullet->render();
	_circleBullet->render();
	////Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void Slime::frame()
{
	switch (_state)
	{
	case SLIMESTATE::SL_IDLE:
		switch (_direction)
		{
		case SLIMEDIRECTION::SL_LEFT:
			_currentFrameY = 1;
			break;

		case SLIMEDIRECTION::SL_RIGHT:
			_currentFrameY = 2;
			break;

		case SLIMEDIRECTION::SL_UP:
			_currentFrameY = 3;
			break;

		case SLIMEDIRECTION::SL_DOWN:
			_currentFrameY = 0;
			break;
		}
		break;

	case SLIMESTATE::SL_MOVE:
		switch (_direction)
		{
		case SLIMEDIRECTION::SL_LEFT:
			_currentFrameY = 5;
			break;

		case SLIMEDIRECTION::SL_RIGHT:
			_currentFrameY = 6;
			break;

		case SLIMEDIRECTION::SL_UP:
			_currentFrameY = 7;
			break;

		case SLIMEDIRECTION::SL_DOWN:
			_currentFrameY = 4;
			break;
		}
		if (!playerCheck())
			randomMove();
		_moveCheck = true;
		break;

	case SLIMESTATE::SL_ATTACK: //����
		switch (_attackParttern) //� ���� ����
		{
		case SLIMEATTACK::SL_PARTTERN1: //������
			switch (_direction) //���� ���� �� ����
			{
			case SLIMEDIRECTION::SL_LEFT:
				_currentFrameY = 9;
				break;

			case SLIMEDIRECTION::SL_RIGHT:
				_currentFrameY = 10;
				break;

			case SLIMEDIRECTION::SL_UP:
				_currentFrameY = 11;
				break;

			case SLIMEDIRECTION::SL_DOWN:
				_currentFrameY = 8;
				break;
			}
			_moveCheck = false;
			circleDirectionBullet();
		break;

		case SLIMEATTACK::SL_PARTTERN2: //3����
			switch (_direction)
			{
			case SLIMEDIRECTION::SL_LEFT:
				_currentFrameY = 17;
				threeDirectionBullet();
				break;

			case SLIMEDIRECTION::SL_RIGHT:
				_currentFrameY = 18;
				threeDirectionBullet();
				break;

			case SLIMEDIRECTION::SL_UP:
				_currentFrameY = 19;
				threeDirectionBullet();
				break;

			case SLIMEDIRECTION::SL_DOWN:
				_currentFrameY = 12;
				break;
			}
			_moveCheck = false;
			threeDirectionBullet();
			break;
		}
		break;

	case SLIMESTATE::SL_DEAD:
		_currentFrameY = 20;
		break;
	}
}

void Slime::animation()
{
	if (_frameSpeed + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		//_image->setFrameY(_frameY);
		_currentFrameX++;

		if (_currentFrameX > _image->getMaxFrameX())
		{
			if (_state == SLIMESTATE::SL_ATTACK)
			{
				_currentFrameX = _image->getMaxFrameX();
				_state = SLIMESTATE::SL_IDLE;
			}

			else
			{
				_currentFrameX = 0;
			}
		}

		_image->setFrameX(_currentFrameX);
	}
}

void Slime::pursuePlayer()
{	
	_state = SLIMESTATE::SL_MOVE;
	_moveCheck = true;
	//���� ����� �ٶ󺸱�
	//�÷��̾� ���� || ���� �Ʒ� || ���� �� �� ���
	if (_playerPos.x < _x || _playerPos.x < _x && _playerPos.y > _y || _playerPos.x < _x && _playerPos.y < _y)
	{
		_direction = SLIMEDIRECTION::SL_LEFT;
	}

	if (_playerPos.x > _x || _playerPos.x > _x && _playerPos.y > _y || _playerPos.x > _x && _playerPos.y < _y)
	{
		_direction = SLIMEDIRECTION::SL_RIGHT;
	}

	////��
	//if (_playerPos.y > CAMERAMANAGER->getDisplayCenterY() && _playerPos.y > _y)
	//{
	//	_direction = SLIMEDIRECTION::SM_UP;
	//}

	////�Ʒ�
	//if (_playerPos.y < CAMERAMANAGER->getDisplayCenterY() && _playerPos.y < _y)
	//{
	//	_direction = SLIMEDIRECTION::SM_DOWN;
	//}

	//�÷��̾� �������� �Ѿư���.
	//_state = SLIMESTATE::SM_MOVE;
	_angle = getAngle(_x, _y, _playerPos.x, _playerPos.y);
	_x += cosf(_angle) * _speed;
	_y += -sinf(_angle) * _speed;
}

void Slime::randomMove()
{
	if (MONSTER_MOVE_RANGE_LEFT < _x &&  _rc.left < MONSTER_MOVE_RANGE_RIGHT)
	{
		_x +=  _randomX * _speed;
	}

	if (MONSTER_MOVE_RANGE_UP < _rc.top && _rc.top < MONSTER_MOVE_RANGE_DOWN)
	{
		_y += _randomY * _speed;
	}
}

bool Slime::playerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
	{
		return true;
	}

	return false;
}

void Slime::randomPosCreate()
{	
	_state = SLIMESTATE::SL_MOVE;
	//������ǥ ����
	if (_rndTimeCount + _moveWorldTime < TIMEMANAGER->getWorldTime())
	{
		_moveWorldTime = TIMEMANAGER->getWorldTime();
		_randomX = RND->getInt(3) - 1;
		_randomY = RND->getInt(3) - 1;
	}

	//��ǥ�� ���� ��� ����
	//���� || ���� �Ʒ� || ���� ��
	if (_randomX == -1 || _randomX == -1 && _randomY == -1 || _randomX == -1 && _randomY == 1)
	{
		_direction = SLIMEDIRECTION::SL_LEFT;
	}

	//������ || ������ �Ʒ� || ������ ��
	if (_randomX == 1 || _randomX == 1 && _randomY == -1 || _randomX == 1 && _randomY == 1)
	{
		_direction = SLIMEDIRECTION::SL_RIGHT;
	}

	//��
	if (_randomY == -1 && _randomX == 0)
	{
		_direction = SLIMEDIRECTION::SL_UP;
	}

	//�Ʒ�
	if (_randomY == 1 && _randomX == 0)
	{
		_direction = SLIMEDIRECTION::SL_DOWN;
	}

	//�������� �������
	if (_randomX == 0 && _randomY == 0)
	{
		_state = SLIMESTATE::SL_IDLE;
	}
	else
		_state = SLIMESTATE::SL_MOVE;
}

void Slime::attackParttern()
{	
	//��Ÿ�� 
	if (ATTACKCOOLTIME + _attacWorldTime < TIMEMANAGER->getWorldTime())
	{
		_attacWorldTime = TIMEMANAGER->getWorldTime();
		_state = SLIMESTATE::SL_ATTACK;
		_attackParttern =  static_cast<SLIMEATTACK>(RND->getInt(2));	
	}

	if (_playerPos.x < _x || _playerPos.x < _x && _playerPos.y > _y || _playerPos.x < _x && _playerPos.y < _y)
	{
		_direction = SLIMEDIRECTION::SL_LEFT;
	}

	if (_playerPos.x > _x || _playerPos.x > _x && _playerPos.y > _y || _playerPos.x > _x && _playerPos.y < _y)
	{
		_direction = SLIMEDIRECTION::SL_RIGHT;
	}
}

void Slime::circleDirectionBullet()
{
	if (_attackParttern == SLIMEATTACK::SL_PARTTERN1 && _image->getMaxFrameX() == _currentFrameX)
	{
		_circleBullet->fire(_rc.left + (_rc.right - _rc.left)/2, _rc.top + (_rc.bottom - _rc.top)/2);
	}
}

void Slime::threeDirectionBullet()
{
	if (_attackParttern == SLIMEATTACK::SL_PARTTERN2 && _image->getMaxFrameX() == _currentFrameX)
	{
		float angle = getAngle(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2, _playerPos.x, _playerPos.y);
		_threeDirectionBullet->fire(_rc.left + (_rc.right - _rc.left) / 2, _rc.top + (_rc.bottom - _rc.top) / 2, angle);
	}
}

STObservedData Slime::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_deadForOb;
	temp.damage = &_attack;
	return temp;
}

void Slime::collideObject(STObservedData obData)
{
	if (((*obData.typeKey) == ObservedType::ROCKET_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD) 
		&& (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
			//���߿� �״� �ִϸ��̼� �ִ°ɷ� �ٲ� ��. isActive�� false�� �ٲٴ� �۾��� ���� �ִϸ��̼� ���� ���� �� �ٲ��ִ� ������ ����	
			_state = SLIMESTATE::SL_DEAD;
			_deadForOb = true;
		}
		else
		{
			_hp -= (*obData.damage);
			if ((*obData.typeKey) != ObservedType::ROCKET_MISSILE)
			{
				_x += cos(*obData.angle) * 5;
				_y += -sin(*obData.angle) * 5;
			}
		}
		(*obData.isActive) = false;
	}
}

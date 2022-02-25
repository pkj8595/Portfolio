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
	_deadForOb = false;
	_deadTimeCount = TIMEMANAGER->getWorldTime() + 9999.999f;
	_x = position.x;
	_y = position.y;
	_randomX = 0;
	_randomY = 0;
	_speed = 0.5f;
	_frameSpeed = 0.3f;
	_index = 0;
	_frameY = 0;
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_randomTimeCount = RND->getFromFloatTo(0.f,2.f);
	_moveWorldTime = TIMEMANAGER->getWorldTime();
	_attacWorldTime = TIMEMANAGER->getWorldTime();
	_playerDistance = 0.0f;
	_range = 300.f;
	_moveCheck = true;
	_isActive = true;
	_attackRange = 150;

	_slimeCirclebullet = new CircleMissile;
	_slimeCirclebullet->init(10, 300);

	_slimebullet = new ThreeDirectionMissile;
	_slimebullet->init(3, 300);
	_hp = 100.0f;

	_direction = SLIMEDIRECTION::SL_DOWN;
	_state = SLIMESTATE::SL_IDLE;

	return S_OK;
}

void Slime::release(void)
{
	Enemy::release();
	_slimeCirclebullet->release();
	SAFE_DELETE(_slimeCirclebullet);
}

void Slime::update(void)
{
	Enemy::update();
	_slimeCirclebullet->update();
	_slimebullet->update();

	//�÷��̾� ���� ������ ������ ���
	if (_deadTimeCount < TIMEMANAGER->getWorldTime() - 0.5f)
	{
		_frameY = 1;
		_state = SLIMESTATE::SL_IDLE;
		_isActive = false;
	}
	if (_state == SLIMESTATE::SL_DEAD)
	{
		if (_index >= _image->getMaxFrameX())
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

	frame();

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

}

void Slime::render(void)
{
	//Enemy::render();
	if(_isActive)
		draw();
}

void Slime::move(void)
{

}

void Slime::draw(void)
{
	animation();
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
	_slimeCirclebullet->render();
	_slimebullet->render();
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
			_frameY = 1;
			break;

		case SLIMEDIRECTION::SL_RIGHT:
			_frameY = 2;
			break;

		case SLIMEDIRECTION::SL_UP:
			_frameY = 3;
			break;

		case SLIMEDIRECTION::SL_DOWN:
			_frameY = 0;
			break;
		}
		break;

	case SLIMESTATE::SL_MOVE:
		switch (_direction)
		{
		case SLIMEDIRECTION::SL_LEFT:
			_frameY = 5;
			break;

		case SLIMEDIRECTION::SL_RIGHT:
			_frameY = 6;
			break;

		case SLIMEDIRECTION::SL_UP:
			_frameY = 7;
			break;

		case SLIMEDIRECTION::SL_DOWN:
			_frameY = 4;
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
				_frameY = 9;
				break;

			case SLIMEDIRECTION::SL_RIGHT:
				_frameY = 10;
				break;

			case SLIMEDIRECTION::SL_UP:
				_frameY = 11;
				break;

			case SLIMEDIRECTION::SL_DOWN:
				_frameY = 8;
				break;
			}
			_moveCheck = false;
			circleDirectionBullet();
		break;

		case SLIMEATTACK::SL_PARTTERN2: //3����
			switch (_direction)
			{
			case SLIMEDIRECTION::SL_LEFT:
				_frameY = 17;
				threeDirectionBullet();
				break;

			case SLIMEDIRECTION::SL_RIGHT:
				_frameY = 18;
				threeDirectionBullet();
				break;

			case SLIMEDIRECTION::SL_UP:
				_frameY = 19;
				threeDirectionBullet();
				break;

			case SLIMEDIRECTION::SL_DOWN:
				_frameY = 12; 
				break;
			}
			_moveCheck = false;
			threeDirectionBullet();
			break;
		}
		break;

	case SLIMESTATE::SL_DEAD:
		_frameY = 20;
		break;
	}
}

void Slime::animation()
{
	if (_frameSpeed + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_image->setFrameY(_frameY);
		_index++;

		if (_index > _image->getMaxFrameX())
		{
			if (_state == SLIMESTATE::SL_ATTACK)
			{
				_index = _image->getMaxFrameX();
				_state = SLIMESTATE::SL_IDLE;
			}

			else
			{
				_index = 0;
			}
		}

		_image->setFrameX(_index);
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
	//if (_playerPos.y > CENTER_Y && _playerPos.y > _y)
	//{
	//	_direction = SLIMEDIRECTION::SM_UP;
	//}

	////�Ʒ�
	//if (_playerPos.y < CENTER_Y && _playerPos.y < _y)
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
	if (MOVECOOLTIME + _moveWorldTime < TIMEMANAGER->getWorldTime())
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
		_attackParttern = static_cast<SLIMEATTACK>(RND->getInt(2));	
	}
}

void Slime::circleDirectionBullet()
{
	if (_attackParttern == SLIMEATTACK::SL_PARTTERN1 && _image->getMaxFrameX() == _index)
	{
		_slimeCirclebullet->fire(_x, _y);
	}
}

void Slime::threeDirectionBullet()
{
	if (_attackParttern == SLIMEATTACK::SL_PARTTERN2 && _image->getMaxFrameX() == _index)
	{
		float angle = getAngle(_x, _y, _playerPos.x, _playerPos.y);
		_slimebullet->fire(_x, _y, angle);
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
		}
		(*obData.isActive) = false;
	}
}

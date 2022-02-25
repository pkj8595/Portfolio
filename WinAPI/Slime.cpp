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
	_worldTime = TIMEMANAGER->getWorldTime();
	_frameSpeed = 0.3f;
	_index = 0;
	_frameY = 0;
	_randomTimeCount = RND->getFromFloatTo(0.f,2.f);
	_moveWorldTime = TIMEMANAGER->getWorldTime();
	_attacWorldTime = TIMEMANAGER->getWorldTime();
	_playerDistance = 0.0f;
	_range = 300.f;
	_moveCheck = true;
	_playerCheck = false;
	_attackCheck = false;

	_direction = SLIMEDIRECTION::SM_DOWN;
	_state = SLIMESTATE::SM_IDLE;
	_attackRange = 150;

	_slimeCirclebullet = new CircleMissile;
	_slimeCirclebullet->init(10, 300);

	//_attRect = RectMakeCenter(_x, _y, 150, 150);
	_hp = 100.0f;
	return S_OK;
}

void Slime::release(void)
{
	_slimeCirclebullet->release();
	Enemy::release();
}

void Slime::update(void)
{
	Enemy::update();
	_slimeCirclebullet->update();

	RECT rc;
	//�÷��̾� ���� ������ ������ ���
	if(playerCheck())
	{
		if(_moveCheck)
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
	//cout << "Slime::update(void) ����X:" << _randomX << endl;
	//cout << "Slime::update(void) ����Y:" << _randomY << endl;

	//cout << (int)_state << endl;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	//_attRect = RectMakeCenter(_x, _y + 20, 180, 180);
	/*_slimebullet->update();
	_slimeCirclebullet->update();

	//�÷��̾ ���� ������ ���Դٸ�
	if (playerCheck())
	{

		//���� ��Ÿ� ������ ������ ���
		if (_playerDistance < attRange)
		{	
			_moveCheck = false;
			
			//���� ����
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
}

void Slime::move(void)
{

}

void Slime::draw(void)
{
	animation();
	Rectangle(getMemDC(), _attRect.left, _attRect.top, _attRect.right, _attRect.bottom);
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
	//_slimebullet->render();
	_slimeCirclebullet->render();
	////Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
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
			break;

		case SLIMEDIRECTION::SM_RIGHT:
			_frameY = 6;
			break;

		case SLIMEDIRECTION::SM_UP:
			_frameY = 4;
			break;

		case SLIMEDIRECTION::SM_DOWN:
			_frameY = 7;
			break;
		}
		if (!playerCheck())
			randomMove();
		_moveCheck = true;
		break;

	case SLIMESTATE::SM_ATTACK: //����
		switch (_attackParttern) //� ���� ����
		{
		case SLIMEATTACK::SLIME_PARTTERN1: //������
			switch (_direction) //���� ���� �� ����
			{
			case SLIMEDIRECTION::SM_LEFT:
				_frameY = 9;
				break;

			case SLIMEDIRECTION::SM_RIGHT:
				_frameY = 10;
				break;

			case SLIMEDIRECTION::SM_UP:
				_frameY = 11;
				break;

			case SLIMEDIRECTION::SM_DOWN:
				_frameY = 8;
				break;
			}
			circleDirectionBullet();
			break;

		case SLIMEATTACK::SLIME_PARTTERN2: //3����
			switch (_direction)
			{
			case SLIMEDIRECTION::SM_LEFT:
				_frameY = 14;
				break;

			case SLIMEDIRECTION::SM_RIGHT:
				_frameY = 15;
				break;

			case SLIMEDIRECTION::SM_UP:
				_frameY = 16;
				break;

			case SLIMEDIRECTION::SM_DOWN:
				_frameY = 13;
				break;
			}
			break;
		}
		_moveCheck = false;
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
		{
			if (_state == SLIMESTATE::SM_ATTACK)
			{
				_index = _image->getMaxFrameX();
				_state = SLIMESTATE::SM_IDLE;
			}

			else
				_index = 0;
		}
		_image->setFrameX(_index);
	}
}

void Slime::pursuePlayer()
{	
	_state = SLIMESTATE::SM_MOVE;
	_moveCheck = true;
	//���� ����� �ٶ󺸱�
	//�÷��̾� ���� || ���� �Ʒ� || ���� �� �� ���
	if (_playerPos.x < _x || _playerPos.x < _x && _playerPos.y > _y || _playerPos.x < _x && _playerPos.y < _y)
	{
		_direction = SLIMEDIRECTION::SM_LEFT;
	}

	if (_playerPos.x > _x || _playerPos.x > _x && _playerPos.y > _y || _playerPos.x > _x && _playerPos.y < _y)
	{
		_direction = SLIMEDIRECTION::SM_RIGHT;
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
	_x += _randomX * _speed;
	_y -= _randomY * _speed;
}

bool Slime::playerCheck()
{
	_playerDistance = getDistance(_x, _y, _playerPos.x, _playerPos.y);

	if (_range > _playerDistance)
	{
		_playerCheck = true;
		return true;
	}

	return false;
}

void Slime::randomPosCreate()
{	
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
		_direction = SLIMEDIRECTION::SM_LEFT;
	}

	//������ || ������ �Ʒ� || ������ ��
	if (_randomX == 1 || _randomX == 1 && _randomY == -1 || _randomX == 1 && _randomY == 1)
	{
		_direction = SLIMEDIRECTION::SM_RIGHT;
	}

	//��
	if (_randomY == -1 && _randomX == 0)
	{
		_direction = SLIMEDIRECTION::SM_UP;
	}

	//�Ʒ�
	if (_randomY == 1 && _randomX == 0)
	{
		_direction = SLIMEDIRECTION::SM_DOWN;
	}

	//�������� �������
	if (_randomX == 0 && _randomY == 0)
	{
		_state = SLIMESTATE::SM_IDLE;
	}
	else
		_state = SLIMESTATE::SM_MOVE;
}

void Slime::attackParttern()
{	
	//��Ÿ�� 
	if (ATTACKCOOLTIME + _attacWorldTime < TIMEMANAGER->getWorldTime())
	{
		_attacWorldTime = TIMEMANAGER->getWorldTime();
		_state = SLIMESTATE::SM_ATTACK;
		_attackParttern = SLIMEATTACK::SLIME_PARTTERN1;//static_cast<SLIMEATTACK>(RND->getInt(2));	
	}
}

void Slime::circleDirectionBullet()
{
	if (_attackParttern == SLIMEATTACK::SLIME_PARTTERN1 && _image->getMaxFrameX() == _index)
	{
		_slimeCirclebullet->fire(_x, _y);
	}
}

void Slime::threeDirectionBullet()
{
}

STObservedData Slime::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_isActive;
	temp.damage = &_attack;
	return temp;
}

void Slime::collideObject(STObservedData obData)
{

	if ((*obData.typeKey) == ObservedType::ROCKET_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD && (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
			//���߿� �״� �ִϸ��̼� �ִ°ɷ� �ٲ� ��.  isActive�� false�� �ٲٴ� �۾��� ���� �ִϸ��̼� ���� ���� �� �ٲ��ִ� ������ ����
			_isActive = false;
		}
		else
		{
			_hp -= (*obData.damage);
			(*obData.isActive) = false;
		}
	}
}

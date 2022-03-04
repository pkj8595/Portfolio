#include "Stdafx.h"
#include "MushMan.h"

MushMan::MushMan()
{
}

MushMan::~MushMan()
{
}

HRESULT MushMan::init(const char * imageName, POINT position)
{
	Enemy::init(imageName, position);
	_x = position.x;
	_y = position.y;
	_hp = 50;
	_speed = 0.5f;
	_currentFrameX = 0;
	_currentFrameY = 0;
	_state = MUSHMANSTATE::MU_IDLE;
	_direction = MUSHMANDIRECTION::MU_DOWN;
	_deadForOb = false;
	_mushroomCreateCheck = false;
	_mushroomRenderCheck = false;
	_moveWorldTime = TIMEMANAGER->getWorldTime();
	_plantMushroomWorldTime = TIMEMANAGER->getWorldTime();
	_mushroomLivingTime = TIMEMANAGER->getWorldTime();
	_mushroomAttackTime = TIMEMANAGER->getWorldTime();
	_deadTime = TIMEMANAGER->getWorldTime();

	_mushroomBullet = new GuidedBullet;
	return S_OK;
}

void MushMan::release(void)
{
	if (_mushroom != NULL)
	{
		_mushroom->release();
		SAFE_DELETE(_mushroom);
	}
	Enemy::release();
}

void MushMan::update(void)
{
	Enemy::update();

	if (_mushroomRenderCheck)
		_mushroom->update();

	if (!_deadForOb)
	{
		// �̹� �ɾ��� �ִ� ��츦 �����ϰ� 10�ʸ��� �ѹ��� �ɴ´�
		if (10.f + _plantMushroomWorldTime <= TIMEMANAGER->getWorldTime() && !_mushroomCreateCheck)
		{
			_plantMushroomWorldTime = TIMEMANAGER->getWorldTime();
			_state = MUSHMANSTATE::MU_ATTACK;
		}

		else if (_state != MUSHMANSTATE::MU_ATTACK)
			randomPosCreate();

		//���� ����
		if (_mushroomCreateCheck)
		{
			_angle = getAngle(_mushroom->getX(), _mushroom->getY(), _playerPos.x, _playerPos.y);

			//���� �����ð�
			if (10.f + _mushroomLivingTime <= TIMEMANAGER->getWorldTime())
			{
				_mushroomLivingTime = TIMEMANAGER->getWorldTime();
			}

			if (_mushroom->getHp() <= 10)
			{
				_mushroomRenderCheck = false;
				_mushroomCreateCheck = false;
			}
			else
				_mushroom->fire(_angle);
		}
	}
	else
	{
		_state = MUSHMANSTATE::MU_DEAD;
	}

	frame();

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

void MushMan::render(void)
{
	Enemy::render();

	if (_mushroomRenderCheck)
		_mushroom->render();
}

void MushMan::move(void)
{
}

void MushMan::draw(void)
{
	_image->frameRender(getMemDC(),
		_rc.left - CAMERAMANAGER->getCameraRect().left,
		_rc.top - CAMERAMANAGER->getCameraRect().top,
		_currentFrameX, _currentFrameY);
}

void MushMan::animation(void)
{
	if (0.3f + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_currentFrameX++;

		if (_state == MUSHMANSTATE::MU_DEAD)
		{
			_currentFrameY = 8;
			_maxFrame = 3;

			if (3.f + _deadTime < TIMEMANAGER->getWorldTime())
			{
				_isActive = false;
			}
		}
		else
		{
			if (_currentFrameX > _maxFrame)
			{
				if (_state == MUSHMANSTATE::MU_ATTACK)
				{
					_currentFrameX = 6;
					_state = MUSHMANSTATE::MU_MOVE;
				}
				//else
				_currentFrameX = 0;
			}
		}
		_image->setFrameX(_currentFrameX);
	}
}

void MushMan::frame()
{
	switch (_state)
	{
	case MUSHMANSTATE::MU_IDLE:
		switch (_direction)
		{
		case MUSHMANDIRECTION::MU_LEFT:
			_currentFrameY = 5;
			break;

		case MUSHMANDIRECTION::MU_RIGHT:
			_currentFrameY = 6;
			break;

		case MUSHMANDIRECTION::MU_UP:
			_currentFrameY = 7;
			break;

		case MUSHMANDIRECTION::MU_DOWN:
			_currentFrameY = 4;
			break;
		}
		_maxFrame = 3;
		break;

	case MUSHMANSTATE::MU_MOVE:
		switch (_direction)
		{
		case MUSHMANDIRECTION::MU_LEFT:
			_currentFrameY = 1;
			break;

		case MUSHMANDIRECTION::MU_RIGHT:
			_currentFrameY = 2;
			break;

		case MUSHMANDIRECTION::MU_UP:
			_currentFrameY = 3;
			break;

		case MUSHMANDIRECTION::MU_DOWN:
			_currentFrameY = 0;
			break;
		}
		_maxFrame = 3;
		randomMove();
		break;

	case MUSHMANSTATE::MU_ATTACK:
		_currentFrameY = 9;
		_maxFrame = 6;
		createBullet();
		break;

	case MUSHMANSTATE::MU_DEAD:
		_currentFrameY = 8;
		_maxFrame = 3;
		break;
	}
}

void MushMan::randomPosCreate()
{
	_state = MUSHMANSTATE::MU_MOVE;

	if (1 + _moveWorldTime < TIMEMANAGER->getWorldTime())
	{
		_moveWorldTime = TIMEMANAGER->getWorldTime();
		_randomX = RND->getInt(3) - 1;
		_randomY = RND->getInt(3) - 1;
	}

	//��ǥ�� ���� ��� ����
	//���� || ���� �Ʒ� || ���� ��
	if (_randomX == -1 || _randomX == -1 && _randomY == -1 || _randomX == -1 && _randomY == 1)
	{
		_direction = MUSHMANDIRECTION::MU_LEFT;
	}

	//������ || ������ �Ʒ� || ������ ��
	if (_randomX == 1 || _randomX == 1 && _randomY == -1 || _randomX == 1 && _randomY == 1)
	{
		_direction = MUSHMANDIRECTION::MU_RIGHT;
	}

	//��
	if (_randomY == -1 && _randomX == 0)
	{
		_direction = MUSHMANDIRECTION::MU_UP;
	}

	//�Ʒ�
	if (_randomY == 1 && _randomX == 0)
	{
		_direction = MUSHMANDIRECTION::MU_DOWN;
	}

	//�������� �������
	if (_randomX == 0 && _randomY == 0)
	{
		_state = MUSHMANSTATE::MU_IDLE;
	}
	else
		_state = MUSHMANSTATE::MU_MOVE;
}

void MushMan::randomMove()
{
	if (MONSTER_MOVE_RANGE_LEFT <= _x && _x <= MONSTER_MOVE_RANGE_RIGHT)
	{
		_x += _randomX * _speed;
	}

	if (MONSTER_MOVE_RANGE_UP <= _y && _y <= MONSTER_MOVE_RANGE_DOWN)
	{
		_y += _randomY * _speed;
	}
}

void MushMan::createBullet()
{
	if (_currentFrameX == _maxFrame && !_mushroomCreateCheck)
	{
		_mushroom = new Mushroom;
		_mushroom->init("Mushroom");
		_mushroom->setPos(_x, _y + 13);
		_mushroomRenderCheck = true;
		_mushroomCreateCheck = true; //���� ����
	}
}

STObservedData MushMan::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_deadForOb;
	temp.damage = &_attack;
	return temp;
}

void MushMan::collideObject(STObservedData obData)
{
	if (((*obData.typeKey) == ObservedType::PLAYER_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD)
		&& (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
				
			_deadForOb = true;
		}
		else
		{
			_hp -= (*obData.damage);
			if ((*obData.typeKey) != ObservedType::PLAYER_MISSILE)
			{
				_x += cos(*obData.angle) * 7;
				_y += -sin(*obData.angle) * 7;
			}
		}
		(*obData.isActive) = false;
	}
}

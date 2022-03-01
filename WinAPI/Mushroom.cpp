#include "Stdafx.h"
#include "Mushroom.h"

Mushroom::Mushroom()
{
}

Mushroom::~Mushroom()
{
}

HRESULT Mushroom::init(const char* imageName, POINT position)
{
	Enemy::init(imageName,position);
	//_x = position.x;
	//_y = position.y;
	_hp = 30;
	
	
	return S_OK;
}

void Mushroom::release(void)
{
	Enemy::release();
}

void Mushroom::update(void)
{
	Enemy::update();

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
}

void Mushroom::render(void)
{
	Enemy::render();
}

void Mushroom::move(void)
{
}

void Mushroom::draw(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void Mushroom::animation(void)
{
}

void Mushroom::fire()
{
}

STObservedData Mushroom::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_deadForOb;
	temp.damage = &_attack;
	return temp;
}

void Mushroom::collideObject(STObservedData obData)
{
	if (((*obData.typeKey) == ObservedType::ROCKET_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD)
		&& (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
			//���߿� �״� �ִϸ��̼� �ִ°ɷ� �ٲ� ��. isActive�� false�� �ٲٴ� �۾��� ���� �ִϸ��̼� ���� ���� �� �ٲ��ִ� ������ ����	
			_deadForOb = true;
		}
		else
		{
			_hp -= (*obData.damage);
		}
		(*obData.isActive) = false;
	}
}

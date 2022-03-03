#include "Stdafx.h"
#include "Mushroom.h"

Mushroom::Mushroom()
{
}

Mushroom::~Mushroom()
{
}

HRESULT Mushroom::init(const char* imageName)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_hp = 30;
	_attackTime = TIMEMANAGER->getWorldTime();

	//Observer code
	_type = ObservedType::MINION;
	_isActive = true;
	_deadForOb = false;
	RECTOBSERVERMANAGER->registerObserved(this);

	_bullet = new GuidedBullet;
	_bullet->init(11, 500);

	return S_OK;
}

void Mushroom::release(void)
{
	Enemy::release();
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void Mushroom::update(void)
{
	Enemy::update();
	_bullet->update();

	if (_deadForOb)
		_isActive = false;


	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
}

void Mushroom::render(void)
{
	Enemy::render();
	_bullet->render();
}

void Mushroom::move(void)
{
}

void Mushroom::draw(void)
{
	_image->render(getMemDC(), _rc.left - CAMERAMANAGER->getCameraRect().left, _rc.top - CAMERAMANAGER->getCameraRect().top);
}

void Mushroom::animation(void)
{
}

void Mushroom::fire(float angle)
{
	if (3.f + _attackTime <= TIMEMANAGER->getWorldTime())
	{
		_attackTime = TIMEMANAGER->getWorldTime();
		_bullet->fire(_x, _y, angle);
	}
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
			//나중에 죽는 애니메이션 넣는걸로 바꿀 것. isActive를 false로 바꾸는 작업은 죽은 애니메이션 전부 실행 뒤 바꿔주는 것으로 변경	
			_deadForOb = true;
		}
		else
		{
			_hp -= (*obData.damage);
		}
		(*obData.isActive) = false;
	}
}

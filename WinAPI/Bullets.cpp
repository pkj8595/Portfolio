#include "Stdafx.h"
#include "Bullets.h"


//=============================================
// ### AMissile ###
//=============================================

HRESULT AMissile::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void AMissile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->release();
		SAFE_DELETE((*_viBullet)->img);
		SAFE_DELETE((*_viBullet)->reflectImg);
	}
	_vBullet.clear();
}

void AMissile::update(void)
{
	move();
	isRange();
	CheckFire();
}

void AMissile::render(void)
{
	draw();
}

void AMissile::fire(float x, float y)
{

}

void AMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->frameRender(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);

		(*_viBullet)->count++;
		if ((*_viBullet)->count % 3 == 0)
		{
			(*_viBullet)->img->setFrameX((*_viBullet)->img->getFrameX() + 1);
			if ((*_viBullet)->img->getFrameX() >= (*_viBullet)->img->getMaxFrameX())
			{
				(*_viBullet)->img->setFrameX(0);
			}
			(*_viBullet)->count = 0;
		}
	}
}

void AMissile::move(void)
{

}

void AMissile::isRange()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		//사거리 밖으로 나갔음
		if (_range < getDistance((*_viBullet)->fireX, (*_viBullet)->fireY, (*_viBullet)->x, (*_viBullet)->y + 100))
		{
			(*_viBullet)->fire = false;
			(*_viBullet)->release();
			SAFE_DELETE((*_viBullet)->img);
			SAFE_DELETE((*_viBullet)->reflectImg);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void AMissile::CheckFire()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!(*_viBullet)->fire)
		{
			SAFE_DELETE((*_viBullet)->img);
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}
	}
}



//=============================================
// ### Bullet ###
//=============================================

HRESULT Bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;
	
	return S_OK;
}

void Bullet::release(void)
{
	_vBullet.clear();
}

void Bullet::update(void)
{
	CheckFire();
	move();
}

void Bullet::render(void)
{
	draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
	//최대 발사갯수 막는다.
	if (_bulletMax <= _vBullet.size()) return;
	
	tagCBullet* bullet = new tagCBullet;
	bullet->img = IMAGEMANAGER->findImage(_imageName);
	bullet->speed = speed;
	bullet->angle = angle;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getFrameHeight(), bullet->img->getFrameHeight());
	bullet->type = ObservedType::MINION_MISSILE;
	bullet->fire = true;
	bullet->magic = false;
	bullet->count = RND->getFromIntTo(1, 16);
	bullet->init();

	_vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		(*_viBullet)->img->frameRender(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top, (*_viBullet)->count,1);
	}
}



void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();) 
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y, (*_viBullet)->img->getFrameWidth(), (*_viBullet)->img->getFrameHeight());
		if (_range < getDistance((*_viBullet)->fireX, (*_viBullet)->fireY, (*_viBullet)->x, (*_viBullet)->y))
		{
			(*_viBullet)->fire = false;
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void Bullet::CheckFire(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!(*_viBullet)->fire)
		{
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}
	}
}

void Bullet::removeBullet(int arrNum)
{
	(*_viBullet)->fire = false;
	(*_viBullet)->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}


//==================================
// ### LinearMissile ###
//==================================

HRESULT LinearMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	return S_OK;
}

void LinearMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	{
		(*_viBullet)->y -= (*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void LinearMissile::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;
	tagCBullet* bullet = new tagCBullet;
	bullet->img = new my::Image;
	bullet->type = ObservedType::ROCKET_MISSILE;
	bullet->img->init("Resource/Images/Project/playerBullet3.bmp", 14, 18,  true, RGB(255, 0, 255));
	bullet->speed = 15.0f;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
	bullet->fire = true;
	bullet->magic = false;
	bullet->init();

	_vBullet.push_back(bullet);
}

void LinearMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

//==================================
// ### CaseShotMissile ###
//==================================

HRESULT CaseShotMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bulletCount = 0;
	_firstAngle = (PI/2)+(static_cast<float>(bulletMax / 2)*_offsetAngle);
	return S_OK;
}

void CaseShotMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void CaseShotMissile::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i < _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->img->init("Resource/Images/Project/playerBullet1.bmp",14, 15,true, RGB(255, 0, 255));
		bullet->type = ObservedType::ROCKET_MISSILE;
		bullet->speed = 4.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = _firstAngle - (_bulletCount*_offsetAngle);
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->fire = true;
		bullet->magic = false;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
	
}
void CaseShotMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);

	}
}

//==================================
// ### BlackholeMissile ###
//==================================
HRESULT BlackholeMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	return S_OK;
}

void BlackholeMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	{
		(*_viBullet)->y -= (*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getFrameWidth(), (*_viBullet)->img->getFrameHeight());
	}
}

void BlackholeMissile::fire(float x, float y)
{
	//최대 발사 갯수를 막는다.
	if (_bulletMax <= _vBullet.size())return;

	//메모리 블록 크기 만큼 
	tagCBullet* bullet= new tagCBullet;
	bullet->type = ObservedType::ROCKET_MISSILE;
	bullet->img = new my::Image;
	bullet->img->init("Resource/Images/Rocket/Missile.BMP", 0.0f, 0.0f, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet->speed = 4.0f;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getFrameWidth(), bullet->img->getFrameHeight());
	bullet->fire = true;
	bullet->magic = false;
	bullet->init();

	_vBullet.push_back(bullet);
}

//==================================
// ### tagCBullet ###
//==================================
void tagCBullet::init(void)
{
	RECTOBSERVERMANAGER->registerObserved(this);
}

void tagCBullet::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
}

STObservedData tagCBullet::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &rc;
	temp.typeKey = &type;
	temp.isActive = &fire;
	temp.damage = &damage;
	temp.angle = &angle;
	temp.magic = &magic;
	return temp;
}

void tagCBullet::collideObject(STObservedData obData)
{
	if ((*obData.typeKey) == ObservedType::ROCKET) fire = false;
	else if ((*obData.typeKey) == ObservedType::PLAYER_SWORD)
	{
		//반격, 공격반사 처리
		angle = (*obData.angle);
		type = ObservedType::ROCKET_MISSILE;
	}
}


//==================================
// ### ThreeDirectionMissile ###
//==================================
HRESULT ThreeDirectionMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bulletCount = 0;
	//_firstAngle = (PI / 2) + (static_cast<float>(bulletMax / 2)*_offsetAngle);

	return S_OK;
}

void ThreeDirectionMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void ThreeDirectionMissile::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i < _bulletMax; i++)
	{
		_firstAngle = angle + (static_cast<float>(_bulletMax / 2)*_offsetAngle);
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->reflectImg = new my::Image;
		//
		bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->reflectImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectBullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->type = ObservedType::MINION_MISSILE;
		bullet->speed = 3.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = _firstAngle - (_bulletCount*_offsetAngle);
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->damage = 1.0f;
		bullet->fire = true;
		bullet->magic = false;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
}

void ThreeDirectionMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if ((*_viBullet)->type == ObservedType::MINION_MISSILE) (*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		else (*_viBullet)->reflectImg->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

//==================================
// ### CircleMissile ###
//==================================

HRESULT CircleMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bulletCount = 0;
	_firstAngle = (PI / 2) + (static_cast<float>(bulletMax / 2)*_offsetAngle);

	return S_OK;
}

void CircleMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void CircleMissile::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i < _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->reflectImg = new my::Image;
		//
		bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->reflectImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectBullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->type = ObservedType::MINION_MISSILE;
		bullet->speed = 3.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = _firstAngle - (_bulletCount*_offsetAngle);
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->fire = true;
		bullet->magic = false;
		bullet->damage = 1.0f;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
}

void CircleMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if ((*_viBullet)->type == ObservedType::MINION_MISSILE) (*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		else (*_viBullet)->reflectImg->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

//==================================
// ### TwoDirectionMissile ###
//==================================
HRESULT TwoDirectionMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bulletCount = 0;
	//_firstAngle = (PI / 2) + (static_cast<float>(bulletMax / 2)*_offsetAngle);

	return S_OK;
}

void TwoDirectionMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void TwoDirectionMissile::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i < _bulletMax; i++)
	{
		_firstAngle = angle + (static_cast<float>(_bulletMax / 2)*_offsetAngle);
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->reflectImg = new my::Image;
		//
		bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->reflectImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectBullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->type = ObservedType::MINION_MISSILE;
		bullet->speed = 3.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = _firstAngle - (_bulletCount*_offsetAngle);
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->fire = true;
		bullet->magic = false;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
}

void TwoDirectionMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if ((*_viBullet)->type == ObservedType::MINION_MISSILE) (*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		else (*_viBullet)->reflectImg->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}


//==================================
// ### Boss Normal Bullets ###
//==================================

HRESULT NormalBullet::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);

	return S_OK;
}

void NormalBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->angle += (*_viBullet)->rotateAngle;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void NormalBullet::fire(float x, float y, float angle, float speed, float rotate)
{
	tagCBullet* bullet = new tagCBullet;
	bullet->img = new my::Image;
	bullet->reflectImg = new my::Image;
	//
	bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet.bmp", 26, 26, true, RGB(255, 0, 255));
	bullet->reflectImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectBullet.bmp", 26, 26, true, RGB(255, 0, 255));
	bullet->type = ObservedType::MINION_MISSILE;
	bullet->speed = speed;
	bullet->damage = 1.0f;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->angle = angle;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
	bullet->fire = true;
	bullet->magic = false;
	bullet->init();
	bullet->rotateAngle = rotate;
	_vBullet.push_back(bullet);
}

void NormalBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if ((*_viBullet)->type == ObservedType::MINION_MISSILE) (*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		else (*_viBullet)->reflectImg->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

//==================================
// ### Boss Normal Bullets ###
//==================================

HRESULT BubbleBullet::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bigImg = new my::Image;
	_reflectbigImg = new my::Image;

	_bigImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/BigBullet.bmp", 52, 52, true, RGB(255, 0, 255));
	_reflectbigImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectBigBullet.bmp", 52, 52, true, RGB(255, 0, 255));
	return S_OK;
}

void BubbleBullet::move(void)
{
	count++;
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (count == 100)
		{
			(*_viBullet)->angle = (*_viBullet)->rotateAngle;
		}
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}

	if (_vBullet.size() == 0) count = 0;
}

void BubbleBullet::fire(float x, float y, float angle, float speed, float rotateAngle)
{
	tagCBullet* bullet = new tagCBullet;
	bullet->img = new my::Image;
	bullet->reflectImg = new my::Image;
	//
	bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet.bmp", 26, 26, true, RGB(255, 0, 255));
	bullet->reflectImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectBullet.bmp", 26, 26, true, RGB(255, 0, 255));
	bullet->type = ObservedType::MINION_MISSILE;
	bullet->speed = speed;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->angle = angle;
	bullet->damage = 1.0f;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
	bullet->fire = true;
	bullet->magic = false;
	bullet->init();
	bullet->rotateAngle = rotateAngle;
	_vBullet.push_back(bullet);
}

void BubbleBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (count < 100)
		{
			if ((*_viBullet)->type == ObservedType::MINION_MISSILE) _bigImg->render(getMemDC(), (*_viBullet)->rc.left - 13, (*_viBullet)->rc.top - 13);
			else _reflectbigImg->render(getMemDC(), (*_viBullet)->rc.left - 13, (*_viBullet)->rc.top - 13);
		}
		else
		{
			if ((*_viBullet)->type == ObservedType::MINION_MISSILE) (*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
			else (*_viBullet)->reflectImg->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		}
	}
}

//==================================
// ### Rafflesia Thorn Bullets ###
//==================================

HRESULT ThornBullet::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);

	return S_OK;
}

void ThornBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void ThornBullet::fire(float x, float y)
{
	for (int i = 0; i < _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/RafflesiaBullet.bmp", 77, 74, true, RGB(255, 0, 255));
		bullet->type = ObservedType::MINION_MISSILE;
		bullet->speed = 3.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->damage = 1.0f;
		bullet->fire = true;
		bullet->magic = false;
		bullet->init();
		_vBullet.push_back(bullet);
	}
}

void ThornBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

HRESULT FairyBullet::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);

	return S_OK;
}

void FairyBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y, (*_viBullet)->img->getFrameWidth(), (*_viBullet)->img->getFrameHeight());	
	}
}

void FairyBullet::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i < _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		//
		bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->type = ObservedType::MINION_MISSILE;
		bullet->speed = 2.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = angle;
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->fire = true;
		bullet->magic = false;
		bullet->init();
		_vBullet.push_back(bullet);
	}
}

void FairyBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

HRESULT SpreadBullet::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bulletCount = 0;
	_firstAngle = (PI / 2) + (static_cast<float>(bulletMax / bulletMax)*_offsetAngle);
	return S_OK;
}

void SpreadBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void SpreadBullet::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i <= _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->reflectImg = new my::Image;
		//
		bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->reflectImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectBullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->type = ObservedType::MINION_MISSILE;
		bullet->speed = 1.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = _firstAngle - (_bulletCount*_offsetAngle);
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->fire = true;
		bullet->magic = false;
		bullet->damage = 1.0f;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
}

void SpreadBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if ((*_viBullet)->type == ObservedType::MINION_MISSILE) (*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		else (*_viBullet)->reflectImg->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

HRESULT SectorBullet::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bulletCount = 0;
	_firstAngle = (PI / 2) + (static_cast<float>(bulletMax / 2)*_offsetAngle);
	return S_OK;
}

void SectorBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void SectorBullet::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i <= _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->reflectImg = new my::Image;
		//
		bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->reflectImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectBullet.bmp", 26, 26, true, RGB(255, 0, 255));
		bullet->type = ObservedType::MINION_MISSILE;
		bullet->speed = 1.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = _firstAngle - (_bulletCount*_offsetAngle);
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->fire = true;
		bullet->magic = false;
		bullet->damage = 1.0f;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
}

void SectorBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if ((*_viBullet)->type == ObservedType::MINION_MISSILE) (*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		else (*_viBullet)->reflectImg->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

HRESULT GuidedBullet::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_firstAngle = (PI / 2) + (static_cast<float>(bulletMax / 2)*_offsetAngle);

	return S_OK;
}

void GuidedBullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x = cosf((*_viBullet)->angle)*(*_viBullet)->speed + (*_viBullet)->x;
		(*_viBullet)->y = -sinf((*_viBullet)->angle)*(*_viBullet)->speed + (*_viBullet)->y;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void GuidedBullet::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i < _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->reflectImg = new my::Image;
		//
		bullet->img->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/Bullet4.bmp", 32, 32, true, RGB(255, 0, 255));
		bullet->reflectImg->init("Resource/Images/Lucie/CompleteImg/Enemy/Monster/ReflectSmallBullet.bmp", 32, 32, true, RGB(255, 0, 255));
		bullet->type = ObservedType::MINION_MISSILE;
		bullet->speed = 1.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = angle;
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->damage = 1.0f;
		bullet->fire = true;
		bullet->magic = false;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
}

void GuidedBullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if ((*_viBullet)->type == ObservedType::MINION_MISSILE) (*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		else (*_viBullet)->reflectImg->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
	}
}

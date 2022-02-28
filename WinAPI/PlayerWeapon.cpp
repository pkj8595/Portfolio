#include "Stdafx.h"
#include "PlayerWeapon.h"

//==================================
// ### tagWeapon ###
//==================================
void tagWeapon::init(void)
{
	RECTOBSERVERMANAGER->registerObserved(this);
}

void tagWeapon::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
}

STObservedData tagWeapon::getRectUpdate()
{
	STObservedData temp;
	
	temp.rc = &rc;
	temp.typeKey = &type;
	temp.isActive = &fire;
	temp.angle = &angle;
	temp.damage = &damage;
	return temp;
}

void tagWeapon::collideObject(STObservedData obData)
{
	if ((*obData.typeKey) == ObservedType::MINION)
	{
		if(!sword) fire = false;
		
	}
}

HRESULT NormalWeapon::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void NormalWeapon::release(void)
{
	_viWeapon = _vWeapon.begin();
	for (; _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		SAFE_DELETE((*_viWeapon)->img);
	}
	_vWeapon.clear();
}

void NormalWeapon::update(void)
{
	move();
}

void NormalWeapon::render(void)
{
	draw();
}

void NormalWeapon::fire(float damage, float x, float y, float angle)
{
	if (_bulletMax <= _vWeapon.size()) return;
	tagWeapon* weapon = new tagWeapon;
	weapon->type = ObservedType::ROCKET_MISSILE;
	weapon->img = new my::Image;
	weapon->img->init("Resource/Images/Lucie/CompleteImg/effect/NormalBullet_effect.bmp", 50, 50, true, RGB(255, 0, 255));
	weapon->fire = true;
	weapon->speed = 30.0f;
	weapon->angle = angle;
	weapon->damage = damage;
	weapon->x = weapon->fireX = x;
	weapon->y = weapon->fireY = y;
	weapon->rc = RectMakeCenter(weapon->x, weapon->y, weapon->img->getWidth(), weapon->img->getHeight());
	_vWeapon.push_back(weapon);
	weapon->init();
}

void NormalWeapon::draw()
{
	_viWeapon = _vWeapon.begin();
	for (; _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		(*_viWeapon)->img->render(getMemDC(), (*_viWeapon)->rc.left, (*_viWeapon)->rc.top);
	}
}

void NormalWeapon::move()
{
	_viWeapon = _vWeapon.begin();
	for (; _viWeapon != _vWeapon.end();)
	{
		(*_viWeapon)->x += (*_viWeapon)->speed * cos((*_viWeapon)->angle);
		(*_viWeapon)->y += -1 * (*_viWeapon)->speed * sin((*_viWeapon)->angle);
		(*_viWeapon)->rc = RectMakeCenter((*_viWeapon)->x, (*_viWeapon)->y, (*_viWeapon)->img->getWidth(), (*_viWeapon)->img->getHeight());
		if (_range < getDistance((*_viWeapon)->fireX, (*_viWeapon)->fireY, (*_viWeapon)->x, (*_viWeapon)->y + 100))
		{
			(*_viWeapon)->release();
			SAFE_DELETE((*_viWeapon)->img);
			_viWeapon = _vWeapon.erase(_viWeapon);
		}
		else if (!(*_viWeapon)->fire)
		{
			(*_viWeapon)->release();
			SAFE_DELETE((*_viWeapon)->img);
			_viWeapon = _vWeapon.erase(_viWeapon);
		}
		else
		{
			++_viWeapon;
		}

	}
}
void NormalWeapon::removeBullet(int index)
{
	_vWeapon[index]->release();
	SAFE_DELETE(_vWeapon[index]->img);
	_vWeapon.erase(_vWeapon.begin() + index);
}



HRESULT SwordWeapon::init(float* x, float* y)
{
	_x = x;
	_y = y;
	_effectMax = 5;
	return S_OK;
}

void SwordWeapon::release(void)
{
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		SAFE_DELETE((*_viWeapon)->img);
	}
	_vWeapon.clear();
}

void SwordWeapon::update(void)
{
	move();
	updateFrame();
}

void SwordWeapon::render(void)
{
	draw();
}

void SwordWeapon::fire(float damage, int combo, int direction)
{
	if (_effectMax <= _vWeapon.size()) return;
	tagWeapon* effect = new tagWeapon;
	effect->type = ObservedType::PLAYER_SWORD;
	effect->img = new my::Image;
	switch (combo)
	{
	case 0: effect->img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect1.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	case 1: effect->img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect2.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	case 2: effect->img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect1.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	case 3: effect->img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect2.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	case 4: effect->img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect3.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	}
	effect->fire = true;
	effect->weaponTick = TIMEMANAGER->getWorldTime();
	effect->img->setFrameX(0);
	effect->sword = true;
	(combo == 0) ? effect->firstHit = true : effect->firstHit = false;
	switch (direction)
	{
	case 0: effect->img->setFrameY(5); _fixX = -30; _fixY = 30; effect->angle = 225 * PI / 180; break;
	case 1: effect->img->setFrameY(4); _fixX = 0; _fixY = 30; effect->angle = 270 * PI / 180; break;
	case 2: effect->img->setFrameY(3); _fixX = 30; _fixY = 30; effect->angle = 315 * PI / 180; break;
	case 3: effect->img->setFrameY(6); _fixX = -30; _fixY = 0; effect->angle = 180 * PI / 180; break;
	case 4: effect->img->setFrameY(2); _fixX = 30; _fixY = 0; effect->angle = 0 * PI / 180; break;
	case 5: effect->img->setFrameY(7); _fixX = -30; _fixY = -30; effect->angle = 135 * PI / 180; break;
	case 6: effect->img->setFrameY(0); _fixX = 0; _fixY = -30; effect->angle = 90 * PI / 180; break;
	case 7: effect->img->setFrameY(1); _fixX = 30; _fixY = -30; effect->angle = 45 * PI / 180; break;
	default: effect->angle = 0; break;
	}
	effect->damage = damage;
	effect->x = *_x + 50 + _fixX;
	effect->y = *_y + 50 + _fixY;
	effect->imageRc = RectMakeCenter(effect->x, effect->y, effect->img->getFrameWidth(), effect->img->getFrameHeight());
	effect->rc = RectMakeCenter(effect->imageRc.left + 96 , effect->imageRc.top + 96, effect->img->getFrameWidth() / 2, effect->img->getFrameHeight() / 2);
	effect->init();
	_vWeapon.push_back(effect);

}

void SwordWeapon::draw()
{
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		(*_viWeapon)->img->frameRender(getMemDC(), (*_viWeapon)->imageRc.left, (*_viWeapon)->imageRc.top);
	}
}

void SwordWeapon::move()
{
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end();)
	{
		(*_viWeapon)->x = *_x + 50 + _fixX;
		(*_viWeapon)->y = *_y + 50 + _fixY;
		if ((*_viWeapon)->img->getFrameX() == (*_viWeapon)->img->getMaxFrameX())
		{
			(*_viWeapon)->release();
			SAFE_DELETE((*_viWeapon)->img);
			_viWeapon = _vWeapon.erase(_viWeapon);
		}
		else ++_viWeapon;
	}
}

void SwordWeapon::updateFrame()
{
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		if ((*_viWeapon)->weaponTick + 0.01f <= TIMEMANAGER->getWorldTime())
		{
			(*_viWeapon)->img->setFrameX((*_viWeapon)->img->getFrameX() + 1);
			(*_viWeapon)->weaponTick = TIMEMANAGER->getWorldTime();
		}
	}
}

HRESULT BowWeapon::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;
	return S_OK;
}

void BowWeapon::release(void)
{
	_viWeapon = _vWeapon.begin();
	for (; _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		SAFE_DELETE((*_viWeapon)->img);
	}
	_vWeapon.clear();
}

void BowWeapon::update(void)
{
	move();
}

void BowWeapon::render(void)
{
	draw();
}

void BowWeapon::fire(float damage, float x, float y, float angle)
{
	if (_bulletMax <= _vWeapon.size()) return;
	tagWeapon* weapon = new tagWeapon;
	weapon->type = ObservedType::ROCKET_MISSILE;
	weapon->img = new my::Image;
	weapon->img->init("Resource/Images/Lucie/CompleteImg/effect/bow_effect.bmp", 20, 20, true, RGB(255, 0, 255));
	weapon->fire = true;
	weapon->speed = 30.0f;
	weapon->angle = angle;
	weapon->damage = damage;
	weapon->x = weapon->fireX = x;
	weapon->y = weapon->fireY = y;
	weapon->rc = RectMakeCenter(weapon->x, weapon->y, weapon->img->getWidth(), weapon->img->getHeight());
	_vWeapon.push_back(weapon);
	weapon->init();
}

void BowWeapon::draw()
{
	_viWeapon = _vWeapon.begin();
	for (; _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		(*_viWeapon)->img->render(getMemDC(), (*_viWeapon)->rc.left, (*_viWeapon)->rc.top);
	}
}

void BowWeapon::move()
{
	_viWeapon = _vWeapon.begin();
	for (; _viWeapon != _vWeapon.end();)
	{
		(*_viWeapon)->x += (*_viWeapon)->speed * cos((*_viWeapon)->angle);
		(*_viWeapon)->y += -1 * (*_viWeapon)->speed * sin((*_viWeapon)->angle);
		(*_viWeapon)->rc = RectMakeCenter((*_viWeapon)->x, (*_viWeapon)->y, (*_viWeapon)->img->getWidth(), (*_viWeapon)->img->getHeight());
		if (_range < getDistance((*_viWeapon)->fireX, (*_viWeapon)->fireY, (*_viWeapon)->x, (*_viWeapon)->y + 100))
		{
			(*_viWeapon)->release();
			SAFE_DELETE((*_viWeapon)->img);
			_viWeapon = _vWeapon.erase(_viWeapon);
		}
		else if (!(*_viWeapon)->fire)
		{
			(*_viWeapon)->release();
			SAFE_DELETE((*_viWeapon)->img);
			_viWeapon = _vWeapon.erase(_viWeapon);
		}
		else
		{
			++_viWeapon;
		}
	}
}

void BowWeapon::removeBullet(int index)
{
	_vWeapon[index]->release();
	SAFE_DELETE(_vWeapon[index]->img);
	_vWeapon.erase(_vWeapon.begin() + index);
}


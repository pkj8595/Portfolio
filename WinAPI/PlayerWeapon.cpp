#include "Stdafx.h"
#include "PlayerWeapon.h"


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
		SAFE_DELETE(_viWeapon->img);
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

void NormalWeapon::fire(float x, float y, float angle)
{
	if (_bulletMax <= _vWeapon.size()) return;
	tagWeapon weapon;
	ZeroMemory(&weapon, sizeof(tagWeapon));
	weapon.img = new my::Image;
	weapon.img->init("Resource/Images/Lucie/CompleteImg/effect/NormalBullet_effect.bmp", 50, 50, true, RGB(255, 0, 255));
	weapon.fire = false;
	weapon.speed = 30.0f;
	weapon.angle = angle;
	weapon.x = weapon.fireX = x;
	weapon.y = weapon.fireY = y;
	weapon.rc = RectMakeCenter(weapon.x, weapon.y, weapon.img->getWidth(), weapon.img->getHeight());
	_vWeapon.push_back(weapon);
}

void NormalWeapon::draw()
{
	_viWeapon = _vWeapon.begin();
	for (; _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		_viWeapon->img->render(getMemDC(), _viWeapon->rc.left, _viWeapon->rc.top);
	}
}

void NormalWeapon::move()
{
	_viWeapon = _vWeapon.begin();
	for (; _viWeapon != _vWeapon.end();)
	{
		_viWeapon->x += _viWeapon->speed * cos(_viWeapon->angle);
		_viWeapon->y += -1 * _viWeapon->speed * sin(_viWeapon->angle);
		_viWeapon->rc = RectMakeCenter(_viWeapon->x, _viWeapon->y, _viWeapon->img->getWidth(), _viWeapon->img->getHeight());
		if (_range < getDistance(_viWeapon->fireX, _viWeapon->fireY, _viWeapon->x, _viWeapon->y + 100))
		{
			SAFE_DELETE(_viWeapon->img);
			_viWeapon = _vWeapon.erase(_viWeapon);
		}
		else
		{
			++_viWeapon;
		}

	}
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
		SAFE_DELETE(_viWeapon->img);
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

void SwordWeapon::fire(int combo, int direction)
{
	if (_effectMax <= _vWeapon.size()) return;
	tagWeapon effect;
	ZeroMemory(&effect, sizeof(tagWeapon));

	effect.img = new my::Image;
	switch (combo)
	{
	case 0: effect.img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect1.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	case 1: effect.img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect2.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	case 2: effect.img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect1.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	case 3: effect.img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect2.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	case 4: effect.img->init("Resource/Images/Lucie/CompleteImg/effect/sword_effect3.bmp", 0.0f, 0.0f, 1920, 1536, 10, 8, true, RGB(255, 0, 255)); break;
	}
	effect.fire = false;
	effect.weaponTick = TIMEMANAGER->getWorldTime();
	effect.img->setFrameX(0);
	switch (direction)
	{
	case 0: effect.img->setFrameY(5); _fixX = -30; _fixY = 30; break;
	case 1: effect.img->setFrameY(4); _fixX = 0; _fixY = 30; break;
	case 2: effect.img->setFrameY(3); _fixX = 30; _fixY = 30; break;
	case 3: effect.img->setFrameY(6); _fixX = -30; _fixY = 0; break;
	case 4: effect.img->setFrameY(2); _fixX = 30; _fixY = 0; break;
	case 5: effect.img->setFrameY(7); _fixX = -30; _fixY = -30; break;
	case 6: effect.img->setFrameY(0); _fixX = 0; _fixY = -30; break;
	case 7: effect.img->setFrameY(1); _fixX = 30; _fixY = -30; break;
	}
	effect.x = *_x + 50 + _fixX;
	effect.y = *_y + 50 + _fixY;
	effect.rc = RectMakeCenter(effect.x, effect.y, effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vWeapon.push_back(effect);

}

void SwordWeapon::draw()
{
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		_viWeapon->img->frameRender(getMemDC(), _viWeapon->rc.left, _viWeapon->rc.top);
	}
}

void SwordWeapon::move()
{
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end();)
	{
		_viWeapon->x = *_x + 50 + _fixX;
		_viWeapon->y = *_y + 50 + _fixY;
		_viWeapon->rc = RectMakeCenter(_viWeapon->x, _viWeapon->y, _viWeapon->img->getFrameWidth(), _viWeapon->img->getFrameHeight());
		if (_viWeapon->img->getFrameX() == _viWeapon->img->getMaxFrameX())
		{
			SAFE_DELETE(_viWeapon->img);
			_viWeapon = _vWeapon.erase(_viWeapon);
		}
		else ++_viWeapon;
	}
}

void SwordWeapon::updateFrame()
{
	for (_viWeapon = _vWeapon.begin(); _viWeapon != _vWeapon.end(); ++_viWeapon)
	{
		if (_viWeapon->weaponTick + 0.01f <= TIMEMANAGER->getWorldTime())
		{
			_viWeapon->img->setFrameX(_viWeapon->img->getFrameX() + 1);
			_viWeapon->weaponTick = TIMEMANAGER->getWorldTime();
		}
	}
}

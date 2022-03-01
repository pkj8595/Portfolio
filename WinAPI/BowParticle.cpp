#include "Stdafx.h"
#include "BowParticle.h"

HRESULT BowParticle::init(void)
{
	_particle = IMAGEMANAGER->addImage("BowParticle", "Resource/Images/Lucie/CompleteImg/effect/bow_effect.bmp", 20, 20, true, RGB(255, 0, 255));
	return S_OK;
}

void BowParticle::release(void)
{
}

void BowParticle::update(void)
{
	_viParticle = _vParticle.begin();
	for (; _viParticle != _vParticle.end();)
	{
		_viParticle->x += cos(_viParticle->angle) * _viParticle->speed;
		_viParticle->y += -sin(_viParticle->angle) * _viParticle->speed;
		_viParticle->rc = RectMakeCenter(_viParticle->x, _viParticle->y, 20, 20);
		_viParticle->alpha -= _viParticle->disappearspeed;
		if (_viParticle->alpha < 0)
		{
			_vParticle.erase(_viParticle);
			break;
		}
		else
		{
			++_viParticle;
		}
	}
}

void BowParticle::render(void)
{
	_viParticle = _vParticle.begin();
	for (; _viParticle != _vParticle.end(); ++_viParticle)
	{
		_particle->alphaRender(getMemDC(), _viParticle->rc.left, _viParticle->rc.top, _viParticle->alpha);
	}
}

void BowParticle::createParticle(float x, float y)
{
	Particle temp;
	ZeroMemory(&temp, sizeof(Particle));
	temp.alpha = 128;
	temp.angle = RND->getFloat(PI * 2);
	temp.speed = RND->getFromFloatTo(3.0f, 7.0f);
	temp.disappearspeed = RND->getFromFloatTo(7.0f, 16.0f);
	temp.x = x;
	temp.y = y;
	temp.rc = RectMakeCenter(temp.x, temp.y, 20, 20);
	_vParticle.push_back(temp);
}

#include "Stdafx.h"
#include "SkillParticle.h"

HRESULT SkillParticle::init(void)
{
	_particle = IMAGEMANAGER->addImage("SkillParticle", "Resource/Images/Lucie/CompleteImg/effect/skillParticle.bmp", 50, 50, true, RGB(255, 0, 255));
	return S_OK;
}

void SkillParticle::release(void)
{
}

void SkillParticle::update(void)
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

void SkillParticle::render(void)
{
	_viParticle = _vParticle.begin();
	for (; _viParticle != _vParticle.end(); ++_viParticle)
	{
		_particle->alphaRender(getMemDC(),
			_viParticle->rc.left - CAMERAMANAGER->getCameraRect().left,
			_viParticle->rc.top - CAMERAMANAGER->getCameraRect().top,
			_viParticle->alpha);
	}
}

void SkillParticle::createParticle(float x, float y)
{
	skillParticle temp;
	ZeroMemory(&temp, sizeof(skillParticle));
	temp.alpha = 255;
	temp.angle = RND->getFloat(PI * 2);
	temp.speed = RND->getFromFloatTo(2.0f, 5.0f);
	temp.disappearspeed = RND->getFromFloatTo(3.0f, 7.0f);
	temp.x = x;
	temp.y = y;
	temp.rc = RectMakeCenter(temp.x, temp.y, 20, 20);
	_vParticle.push_back(temp);
}

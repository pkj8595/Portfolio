#include "Stdafx.h"
#include "DamageEffectManager.h"

HRESULT DamageEffectManager::init(void)
{
	return S_OK;
}

void DamageEffectManager::release(void)
{
}

void DamageEffectManager::update(void)
{
	_viDamage = _vDamage.begin();
	for (;_viDamage != _vDamage.end(); ++_viDamage)
	{
		(*_viDamage)->update();

		if (!(*_viDamage)->isShow())
		{
			(*_viDamage)->release();
			SAFE_DELETE(*_viDamage);
			_vDamage.erase(_viDamage);
			break;
		}
	}
}

void DamageEffectManager::render(void)
{
	_viDamage = _vDamage.begin();
	for (; _viDamage != _vDamage.end(); ++_viDamage)
	{
		(*_viDamage)->render();
	}
}

void DamageEffectManager::createDamage(int damage, bool isMagicDamage, float x, float y)
{

	if (damage >= 100)
	{
		createSingleDamage(9, isMagicDamage, x - 10, y);
		createSingleDamage(9, isMagicDamage, x + 10, y);
	}
	else if (damage >= 10)
	{
		createSingleDamage(damage / 10, isMagicDamage, x - 10, y);
		createSingleDamage(damage % 10, isMagicDamage, x + 10, y);
	}
	else if (damage > 0)
	{
		createSingleDamage(damage, isMagicDamage, x, y);
	}
	else return;
}

void DamageEffectManager::createSingleDamage(int damage, bool isMagicDamage, float x, float y)
{
	Damage* temp = new Damage;
	temp->init(damage, isMagicDamage, x, y);
	_vDamage.push_back(temp);
}

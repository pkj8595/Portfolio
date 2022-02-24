#pragma once
#include "GameNode.h"
#include "Damage.h"

class DamageEffectManager : public GameNode
{
private:
	typedef vector<Damage*> vDamage;
	typedef vector<Damage*>::iterator viDamage;

	vDamage _vDamage;
	viDamage _viDamage;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void createDamage(int damage, bool isMagicDamage, float x, float y);
	void createSingleDamage(int damage, bool isMagicDamage, float x, float y);
};


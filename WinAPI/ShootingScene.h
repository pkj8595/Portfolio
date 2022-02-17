#pragma once
#include "GameNode.h"
#include "CProjectPlayer.h"
#include "EnemyManager.h"
#include "EffectManager.h"

#define _USE_MATH_DEFINES
#include "math.h"

#define TILE_MAP_SIZE		25

class ShootingScene : public GameNode
{
private:
	CProjectPlayer* _pPlayer;
	EnemyManager* _em;
	EffectManager* _effectManager;

	float _x, _y;
	bool _isGameStop;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void CheckPlayerIsActive(void);


	ShootingScene() {}
	virtual ~ShootingScene() {}
};
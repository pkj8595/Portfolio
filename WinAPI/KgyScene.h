#pragma once
#include "GameNode.h"
#include "EnemyManager.h"
#include "Player.h"

class KgyScene:public GameNode
{
private:
	EnemyManager* _em;
	RECT _rc;
	POINT _playerpos;
	Player* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	KgyScene();
	virtual ~KgyScene();
};


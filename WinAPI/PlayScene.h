#pragma once
#include "GameNode.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "Player.h"

class PlayScene : public GameNode
{
private:

	MapManager* _mapManager;
	EnemyManager* _enemyManager;
	Player* _player;
	int _stageNum;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void pixelCollision();
	PlayScene();
	~PlayScene() {}
};


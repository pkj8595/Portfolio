#pragma once
#include "GameNode.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "ItemSpawner.h"

class PlayScene : public GameNode
{
private:
	my::Image* _fadeoutImage;
	MapManager* _mapManager;
	EnemyManager* _enemyManager;
	Player* _player;
	ItemSpawner* _itemSpawner;
	int _stageNum;

	bool _isChanging;
	int _fadeoutAlpha;
	int _changeScreenType; //0, 1, 2, 3 : LEFT, RIGHT, UP, DOWN

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void pixelCollision();

	void changeMapFadeOut();
	void setFadeOutAlpha();
	void changeMap();
	void spawnMonster();
	void checkPlayerEscapeWithoutClear();

	PlayScene();
	~PlayScene() {}
};


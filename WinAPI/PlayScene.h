#pragma once
#include "GameNode.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "ItemSpawner.h"
#include "EffectManager.h"

class PlayScene : public GameNode
{
private:
	my::Image* _fadeoutImage;
	my::Image* _gameoverImage;
	my::Image* _clearBossImage;
	my::Image* _clearBossImage2;
	my::Image* _clearBossImage3;
	MapManager* _mapManager;
	EnemyManager* _enemyManager;
	EffectManager* _effectManager;
	Player* _player;
	ItemSpawner* _itemSpawner;
	int _stageNum;
	bool _isChanging;

	int _startAlpha;

	bool _showBossEffect;
	int _frameCount;
	float _bossEffectTime;
	int _bossClearAlpha;

	int _fadeoutAlpha;
	int _changeScreenType; //0, 1, 2, 3 : LEFT, RIGHT, UP, DOWN

	int _deadAlpha;
	float _deadTimer;

	

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void pixelCollision();
	void pixelBulletCollision();

	void changeMapFadeOut();
	void setFadeOutAlpha();
	void changeMap();
	void spawnMonster();
	void checkPlayerEscapeWithoutClear();
	void checkDead();


	PlayScene();
	~PlayScene() {}
};


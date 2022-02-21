#pragma once
#include "GameNode.h"
#include "MapManager.h"
#include "Player.h"

class PlayScene : public GameNode
{
private:

	MapManager* _mapManager;
	Player* _player;
	int _stageNum;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	PlayScene();
	~PlayScene() {}
};


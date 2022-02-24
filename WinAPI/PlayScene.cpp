#include "Stdafx.h"
#include "PlayScene.h"

HRESULT PlayScene::init(void)
{
	_mapManager = new MapManager;
	if (_stageNum == 0)	_mapManager->init(10, _stageNum);
	else _mapManager->init(13, _stageNum);

	_enemyManager = new EnemyManager;
	_enemyManager->init();
	_player = new Player;
	_player->init();

	_enemyManager->setRoketMemoryAddress(_player);
	return S_OK;
}

void PlayScene::release(void)
{
}

void PlayScene::update(void)
{
	_mapManager->update();
	_enemyManager->update();
	_player->update();
}

void PlayScene::render(void)
{
	_mapManager->render();
	_enemyManager->render();
	_player->render();
	if (_mapManager->isMinimapToggle()) _mapManager->printTempMinimap();
	pixelCollision();
}

PlayScene::PlayScene() : _stageNum(0) {
}

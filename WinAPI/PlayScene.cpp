#include "Stdafx.h"
#include "PlayScene.h"

HRESULT PlayScene::init(void)
{
	_mapManager = new MapManager;
	if (_stageNum == 0)	_mapManager->init(10);
	else _mapManager->init(13);
	return S_OK;
}

void PlayScene::release(void)
{
}

void PlayScene::update(void)
{
	_mapManager->update();
}

void PlayScene::render(void)
{
	_mapManager->render();
}

PlayScene::PlayScene() : _stageNum(0) {
}

#include "Stdafx.h"
#include "PlayScene.h"

HRESULT PlayScene::init(void)
{
	_fadeoutImage = IMAGEMANAGER->addImage("Fadeout", "Resource/Images/Lucie/CompleteImg/effect/changeScreen.bmp", 1104, 960, true, RGB(255, 0, 255));
	_mapManager = new MapManager;
	if (_stageNum == 0)	_mapManager->init(13, _stageNum);
	else _mapManager->init(13, _stageNum);
	_itemSpawner = ItemSpawner::getSingleton();
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
	if (_fadeoutAlpha > 252) _fadeoutAlpha = 252;
	RECTOBSERVERMANAGER->update();
	_mapManager->update();
	_enemyManager->update();
	_player->update();
	_itemSpawner->update();

	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		_itemSpawner->createItem(CENTER_X, CENTER_Y, true);
	}

	pixelCollision();
	setFadeOutAlpha();
	changeMapFadeOut();
	changeMap();
	checkPlayerEscapeWithoutClear();

}

void PlayScene::render(void)
{
	_mapManager->render();
	_player->render();
	_player->printStack();
	_enemyManager->render();
	_itemSpawner->render();
	RECTOBSERVERMANAGER->render();

	//UI
	if (_mapManager->isMinimapToggle()) _mapManager->printTempMinimap();
	_player->printUI();
	_player->printInventory();

	//WINSIZE effect
	_player->printHitBG();
	if (_fadeoutAlpha > 0) _fadeoutImage->alphaRender(getMemDC(), _fadeoutAlpha);

}

PlayScene::PlayScene() : _stageNum(0) {
}

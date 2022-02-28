#include "Stdafx.h"
#include "PlayScene.h"




HRESULT PlayScene::init(void)
{
	_fadeoutImage = IMAGEMANAGER->addImage("Fadeout", "Resource/Images/Lucie/CompleteImg/effect/changeScreen.bmp", 1104, 960, true, RGB(255, 0, 255));
	_clearBossImage = IMAGEMANAGER->addFrameImage("BossClear", "Resource/Images/Lucie/CompleteImg/effect/clearBoss1.bmp", 5520, 19200, 5, 20, true, RGB(255,0,255));
	// 주석 제거 금지
	//_clearBossImage2 = IMAGEMANAGER->addFrameImage("BossClear2", "Resource/Images/Lucie/CompleteImg/effect/clearBoss2.bmp", 5520, 19200, 5, 20, true, RGB(255,0,255));
	//_clearBossImage3 = IMAGEMANAGER->addImage("whiteScreen", "Resource/Images/Lucie/CompleteImg/effect/whiteScreen.bmp", 1104, 960, false, RGB(255, 0, 255));

	_mapManager = new MapManager;
	if (_stageNum == 0)	_mapManager->init(13, _stageNum);
	else _mapManager->init(13, _stageNum);

	_itemSpawner = ItemSpawner::getSingleton();

	_enemyManager = new EnemyManager;
	_enemyManager->init();

	_player = new Player;
	_player->init();
	
	_showBossEffect = false;
	_frameCount = 0;
	_bossEffectTime = TIMEMANAGER->getWorldTime();
	_bossClearAlpha = 255;

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

	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		_itemSpawner->createItem(CENTER_X, CENTER_Y, true);
	}

	pixelCollision();
	setFadeOutAlpha();
	changeMapFadeOut();
	changeMap();
	checkPlayerEscapeWithoutClear();

	// 주석 제거 금지
	//if (_showBossEffect)
	//{
	//	if (_bossEffectTime + 0.01f < TIMEMANAGER->getWorldTime())
	//	{
	//		if (_frameCount > 225)
	//		{
	//			_bossClearAlpha -= 4;
	//		}
	//		else
	//		{
	//			_frameCount++;
	//			_bossEffectTime = TIMEMANAGER->getWorldTime();
	//		}
	//	}
	//}
}

void PlayScene::render(void)
{
	_mapManager->render();
	_player->render();
	_player->printStack();
	_enemyManager->render();
	RECTOBSERVERMANAGER->render();

	//UI
	if (_mapManager->isMinimapToggle()) _mapManager->printTempMinimap();
	_player->printUI();
	_player->printInventory();

	//WINSIZE effect
	_player->printHitBG();
	if (_fadeoutAlpha > 0) _fadeoutImage->alphaRender(getMemDC(), _fadeoutAlpha);

	// 주석 제거 금지
	//if (_showBossEffect)
	//{
	//	if(_frameCount < 100) _clearBossImage->frameRender(getMemDC(), 0, 0, (_frameCount % 5), (_frameCount / 5));
	//	else if (_frameCount < 200) _clearBossImage2->frameRender(getMemDC(), 0, 0, (_frameCount % 5), ((_frameCount-100) / 5));
	//	else if (_bossClearAlpha > 0) _clearBossImage3->alphaRender(getMemDC(), _bossClearAlpha);
	//}

}

PlayScene::PlayScene() : _stageNum(0) {
}

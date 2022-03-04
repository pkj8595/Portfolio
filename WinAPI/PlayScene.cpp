#include "Stdafx.h"
#include "PlayScene.h"

HRESULT PlayScene::init(void)
{
	_fadeoutImage = IMAGEMANAGER->addImage("Fadeout", "Resource/Images/Lucie/CompleteImg/effect/changeScreen.bmp", 1104, 960, true, RGB(255, 0, 255));
	_gameoverImage = IMAGEMANAGER->addImage("Gameover", "Resource/Images/Lucie/CompleteImg/pitures/banana256.bmp", 960, 540, true, RGB(255, 0, 255));
	_clearBossImage = IMAGEMANAGER->addFrameImage("BossClear", "Resource/Images/Lucie/CompleteImg/effect/clearBoss1.bmp", 5520, 19200, 5, 20, true, RGB(255,0,255));
	_clearBossImage2 = IMAGEMANAGER->addFrameImage("BossClear2", "Resource/Images/Lucie/CompleteImg/effect/clearBoss2.bmp", 5520, 19200, 5, 20, true, RGB(255,0,255));
	_clearBossImage3 = IMAGEMANAGER->addImage("whiteScreen", "Resource/Images/Lucie/CompleteImg/effect/whiteScreen.bmp", 1104, 960, false, RGB(255, 0, 255));

	_mapManager = new MapManager;
	if (_stageNum == 0)	_mapManager->init(13, _stageNum);
	else _mapManager->init(13, _stageNum);

	_itemSpawner = ItemSpawner::getSingleton();

	_enemyManager = new EnemyManager;
	_enemyManager->init();

	_effectManager = new EffectManager;
	_effectManager->init();

	_player = new Player;
	_player->init();

	_startAlpha = 255;

	_showBossEffect = false;
	_frameCount = 0;
	_bossEffectTime = TIMEMANAGER->getWorldTime();
	_bossClearAlpha = 255;

	_deadAlpha = 0;
	_deadTimer = 0;

	_enemyManager->setPlayerMemoryAddress(_player);


	return S_OK;
}

void PlayScene::release(void)
{
	RECTOBSERVERMANAGER->release();
	_effectManager->release();
	_enemyManager->release();
	_mapManager->release();
	_player->release();
	_itemSpawner->release();

}

void PlayScene::update(void)
{
	if (_startAlpha > 0) _startAlpha -= 4;
	if (_fadeoutAlpha > 252) _fadeoutAlpha = 252;
	RECTOBSERVERMANAGER->update();
	_mapManager->update();
	_enemyManager->update();
	_player->update();
	_effectManager->update();
	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		_itemSpawner->createItem(CAMERAMANAGER->getDisplayCenterX(), CAMERAMANAGER->getDisplayCenterY(), true);
	}

	pixelCollision();
	pixelBulletCollision();
	setFadeOutAlpha();
	changeMapFadeOut();
	changeMap();
	checkPlayerEscapeWithoutClear();

	if (_showBossEffect)
	{
		if (_bossEffectTime + 0.01f < TIMEMANAGER->getWorldTime())
		{
			if (_frameCount > 225)
			{
				_bossClearAlpha -= 4;
			}
			else
			{
				_frameCount++;
				_bossEffectTime = TIMEMANAGER->getWorldTime();
			}
		}
		if (_bossClearAlpha < 0)
		{
			SCENEMANAGER->changeScene("EndingScene");
		}
	}

	checkDead();
	CAMERAMANAGER->update();
}

void PlayScene::render(void)
{
	_mapManager->render();
	_enemyManager->render();
	_player->render();
	_player->printStack();
	RECTOBSERVERMANAGER->render();
	_effectManager->render();
	_mapManager->getCurrentMap()->printOutsideRC();

	if (_mapManager->isMinimapToggle()) _mapManager->printTempMinimap();
	_player->printUI();
	_player->printInventory();
	RECTOBSERVERMANAGER->printTextUI();

	//WINSIZE effect
	_player->printHitBG();
	if (_fadeoutAlpha > 0) _fadeoutImage->alphaRender(getMemDC(), _fadeoutAlpha);
	if (_startAlpha > 0) _fadeoutImage->alphaRender(getMemDC(), _startAlpha);

	
	// 주석 제거 금지
	if (_showBossEffect)
	{
		if(_frameCount < 100) _clearBossImage->frameRender(getMemDC(), -80, - 200, (_frameCount % 5), (_frameCount / 5));
		else if (_frameCount < 200) _clearBossImage2->frameRender(getMemDC(), -80, -200, (_frameCount % 5), ((_frameCount-100) / 5));
		else if (_bossClearAlpha > 0)
		{
			_fadeoutImage->render(getMemDC());
			_clearBossImage3->alphaRender(getMemDC(), _bossClearAlpha);
		}
	}

	if (_player->isDead())
	{
		_fadeoutImage->alphaRender(getMemDC(), _deadAlpha);
		_gameoverImage->alphaRender(getMemDC(), _deadAlpha);
	}
}


PlayScene::PlayScene() : _stageNum(0) {
}

#include "Stdafx.h" 
#include "MainGame.h"
#include "ItemManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "KgyScene.h"
#include "Lobby.h"
#include "ShopScene.h"
#include "EndingScene.h"




inline void MainGame::addSounds(void)
{
	TEMPSOUNDMANAGER->addWaveFileWithKey("Sword1", "Resource/Sound/Lucie/sword1.wav");
	TEMPSOUNDMANAGER->addWaveFileWithKey("Sword2", "Resource/Sound/Lucie/sword2.wav");
	TEMPSOUNDMANAGER->addWaveFileWithKey("Sword3", "Resource/Sound/Lucie/sword3.wav");
	TEMPSOUNDMANAGER->addWaveFileWithKey("Sword4", "Resource/Sound/Lucie/sword4.wav");
	TEMPSOUNDMANAGER->addWaveFileWithKey("Sword5", "Resource/Sound/Lucie/sword5.wav");
	TEMPSOUNDMANAGER->addWaveFileWithKey("Skill", "Resource/Sound/Lucie/skill.wav");
	TEMPSOUNDMANAGER->addWaveFileWithKey("Skillhit", "Resource/Sound/Lucie/skillhit.wav");
	TEMPSOUNDMANAGER->addWaveFileWithKey("Mobhit", "Resource/Sound/Lucie/mobhit.wav");
	
}

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	ItemManager::getSingleton()->init();
	ItemSpawner::getSingleton()->init();
	//addSounds();

	SCENEMANAGER->addScene("TitleScene", new TitleScene);
	SCENEMANAGER->addScene("PlayScene", new PlayScene);
	SCENEMANAGER->addScene("kgy", new KgyScene);
	SCENEMANAGER->addScene("Lobby", new Lobby);
	SCENEMANAGER->addScene("ShopScene", new ShopScene);
	SCENEMANAGER->addScene("EndingScene", new EndingScene);

	SCENEMANAGER->changeScene("EndingScene");
	
	/*SetMapMode(getHDC(), MM_ISOTROPIC);
	RECT cameraRc = RectMake(0, 0, 0, 0);
	GetClientRect(_hWnd, &cameraRc);
	SetWindowExtEx(getHDC(), 960, 540, NULL);
	SetViewportExtEx(getHDC(), cameraRc.right, cameraRc.bottom, NULL);
	*/

	return S_OK;
}

void MainGame::release(void)
{
	ItemManager::getSingleton()->release();
	ItemManager::getSingleton()->releaseSingleton();
	ItemSpawner::getSingleton()->release();
	ItemSpawner::getSingleton()->releaseSingleton();

	GameNode::release();
}

void MainGame::update(void)
{
	
	SCENEMANAGER->update();	
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC());
}


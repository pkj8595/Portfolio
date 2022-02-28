#include "Stdafx.h" 
#include "MainGame.h"
#include "ItemManager.h"
#include "TitleScene.h"
#include "LobbyScene.h"
#include "PlayScene.h"
#include "KgyScene.h"
#include "Lobby.h"
#include "ShopScene.h"


HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	ItemManager::getSingleton()->init();
	ItemSpawner::getSingleton()->init();

	SCENEMANAGER->addScene("TitleScene", new TitleScene);
	SCENEMANAGER->addScene("LobbyScene", new LobbyScene);
	SCENEMANAGER->addScene("PlayScene", new PlayScene);
	SCENEMANAGER->addScene("kgy", new KgyScene);
	SCENEMANAGER->addScene("Lobby", new Lobby);
	SCENEMANAGER->addScene("ShopScene", new ShopScene);

	SCENEMANAGER->changeScene("PlayScene");

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

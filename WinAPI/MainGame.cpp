#include "Stdafx.h" 
#include "MainGame.h"
#include "TitleScene.h"
#include "LobbyScene.h"
#include "PlayScene.h"
#include "KgyScene.h"
#include "OJHScene.h"
#include "Lobby.h"
#include "ShopScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	SCENEMANAGER->addScene("TitleScene", new TitleScene);
	SCENEMANAGER->addScene("LobbyScene", new LobbyScene);
	SCENEMANAGER->addScene("PlayScene", new PlayScene);
	SCENEMANAGER->addScene("kgy", new KgyScene);
	SCENEMANAGER->addScene("TextTest", new OJHScene);
	SCENEMANAGER->addScene("Lobby", new Lobby);
	SCENEMANAGER->addScene("ShopScene", new ShopScene);

	SCENEMANAGER->changeScene("PlayScene");


	return S_OK;
}

void MainGame::release(void)
{
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

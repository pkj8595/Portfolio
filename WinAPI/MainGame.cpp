#include "Stdafx.h" 
#include "MainGame.h"
#include "ShootingScene.h"
#include "TitleScene.h"
#include "LobbyScene.h"
#include "PlayScene.h"
#include "KgyScene.h"
#include "OJHScene.h"
#include "ShopScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	SCENEMANAGER->addScene("����", new ShootingScene);
	SCENEMANAGER->addScene("TitleScene", new TitleScene);
	SCENEMANAGER->addScene("LobbyScene", new LobbyScene);
	SCENEMANAGER->addScene("PlayScene", new PlayScene);
	SCENEMANAGER->addScene("kgy", new KgyScene);

	SCENEMANAGER->changeScene("kgy");
	SCENEMANAGER->addScene("TextTest", new OJHScene);
	SCENEMANAGER->addScene("ShopScene", new ShopScene);

	//SCENEMANAGER->changeScene("ShopScene");

	//SCENEMANAGER->changeScene("TextTest");
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

#include "Stdafx.h" 
#include "MainGame.h"
#include "ShootingScene.h"
#include "TitleScene.h"
#include "LobbyScene.h"
#include "PlayScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	SCENEMANAGER->addScene("½´ÆÃ", new ShootingScene);
	SCENEMANAGER->addScene("TitleScene", new TitleScene);
	SCENEMANAGER->addScene("LobbyScene", new LobbyScene);
	SCENEMANAGER->addScene("PlayScene", new PlayScene);

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

#include "Stdafx.h" 
#include "MainGame.h"
#include "ShootingScene.h"

HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);

	//SCENEMANAGER->addScene("½´ÆÃ", new ShootingScene);
	SCENEMANAGER->changeScene("½´ÆÃ");

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

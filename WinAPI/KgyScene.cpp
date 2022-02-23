#include "Stdafx.h"
#include "KgyScene.h"



KgyScene::KgyScene()
{
	//!Do Nothing
}

KgyScene::~KgyScene()
{
	//!Do Nothing
}

HRESULT KgyScene::init(void)
{
	_em = new EnemyManager;
	_em->init();
	
	_player = new Player;
	_player->init();

	_playerpos.x = CENTER_X - 200;
	_playerpos.y = CENTER_Y;

	return S_OK;
}

void KgyScene::release(void)
{
	_em->release();
	SAFE_DELETE(_em);

	_player->release();
	SAFE_DELETE(_player);
}

void KgyScene::update(void)
{
	_em->setRoketMemoryAddress(_player);
	_em->update();
	_player->update();
}

void KgyScene::render(void)
{
	_em->render();
	_player->render();
}

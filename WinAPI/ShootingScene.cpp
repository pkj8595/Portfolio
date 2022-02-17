#include "Stdafx.h"
#include "ShootingScene.h"


HRESULT ShootingScene::init(void)
{
	_isGameStop = false;

	IMAGEMANAGER->addImage("basebk", "Resource/Images/Project/basebk.bmp", 413, 407);

	_pPlayer = new CProjectPlayer;
	_pPlayer->init();

	_em = new EnemyManager;
	_em->init();

	_effectManager = new EffectManager;
	_effectManager->init();

	_em->setRoketMemoryAddress(_pPlayer);
	_x = _y = 0.0f;

	RECTOBSERVERMANAGER->registerEffectManagerAddress(_effectManager);

	return S_OK;
}

void ShootingScene::release(void)
{

	_pPlayer->release();
	SAFE_DELETE(_pPlayer);
	_em->release();
	SAFE_DELETE(_em);
	_effectManager->release();
	SAFE_DELETE(_effectManager);

}

void ShootingScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F10)) _isGameStop = !_isGameStop;
	if (_isGameStop) return;
	_pPlayer->update();
	_em->update();
	_effectManager->update();
	RECTOBSERVERMANAGER->getRectFromObserved();
	CheckPlayerIsActive();

	_y -= 3;
}

void ShootingScene::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	RECT rc = { 0,0,WINSIZE_X,WINSIZE_Y };
	IMAGEMANAGER->findImage("basebk")->loopRender(getMemDC(), &rc, _x, _y);

	_pPlayer->render();
	_em->render();
	_effectManager->render();


	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC());
}

void ShootingScene::CheckPlayerIsActive(void)
{
	if (!_pPlayer->getIsActive())
	{
		_isGameStop = true;
	}
}



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

	return S_OK;
}

void KgyScene::release(void)
{
	_em->release();
	SAFE_DELETE(_em);
}

void KgyScene::update(void)
{
	_em->update();
}

void KgyScene::render(void)
{
	_em->render();
}

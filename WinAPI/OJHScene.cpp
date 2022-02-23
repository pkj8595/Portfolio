#include "Stdafx.h"
#include "OJHScene.h"
#include "TextSystemManager.h"

HRESULT OJHScene::init(void)
{
	_tsm = new TextSystemManager;
	_tsm->init();

	return S_OK;
}

void OJHScene::release(void)
{
	_tsm->release();
	SAFE_DELETE(_tsm);
}

void OJHScene::update(void)
{
	_tsm->update(0);
}

void OJHScene::render(void)
{
	_tsm->render(0);
}

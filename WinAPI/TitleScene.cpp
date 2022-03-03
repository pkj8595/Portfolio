#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("TitleBG", "Resource/Images/Lucie/CompleteImg/title/TitleBackground.bmp", 960, 540);
	_gameName = IMAGEMANAGER->addImage("TitleName", "Resource/Images/Lucie/CompleteImg/title/Title.bmp", 960, 540, true, RGB(255, 0, 255));
	_start = IMAGEMANAGER->addFrameImage("Start", "Resource/Images/Lucie/CompleteImg/title/Command_0.bmp", 130, 60, 1, 2, true, RGB(255, 0, 255));
	_continue = IMAGEMANAGER->addFrameImage("Continue", "Resource/Images/Lucie/CompleteImg/title/Command_1.bmp", 130, 60, 1, 2, true, RGB(255, 0, 255));
	_exit = IMAGEMANAGER->addFrameImage("Exit", "Resource/Images/Lucie/CompleteImg/title/Command_3.bmp", 130, 60, 1, 2, true, RGB(255, 0, 255));
	_changeScreen = IMAGEMANAGER->addImage("TitleBlackScreen", "Resource/Images/Lucie/CompleteImg/effect/changeScreen.bmp", 1104, 960);

	_bgRc = RectMake(0, 0, _bg->getWidth(), _bg->getHeight());
	_startRc = RectMake(CAMERAMANAGER->getDisplayCenterX() - 100,
		CAMERAMANAGER->getDisplayCenterY() + 50,
		_start->getFrameWidth(), _start->getFrameHeight());
	_exitRc = RectMake(CAMERAMANAGER->getDisplayCenterX() - 100, CAMERAMANAGER->getDisplayCenterY() + 100, _exit->getFrameWidth(), _exit->getFrameHeight());

	changeScreenAlpha = 0.0f;

	_isStart = false;

	return S_OK;
}

void TitleScene::release(void)
{
}

void TitleScene::update(void)
{

	if (PtInRect(&_startRc, _ptMouse))
	{
		_start->setFrameY(1);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/ui_ok.wav");
			_isStart = true;
		}
		
	}
	else _start->setFrameY(0);

	if (PtInRect(&_exitRc, _ptMouse))
	{
		_exit->setFrameY(1);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/ui_ok.wav");
			Sleep(500);
			PostQuitMessage(0);
		}
	}
	else _exit->setFrameY(0);

	if (changeScreenAlpha > 252)
	{
		changeScreenAlpha = 252;
		SCENEMANAGER->changeScene("Lobby");
	}

	if (_isStart)
	{
		changeScreenAlpha += 3.0f;
	}
	

}

void TitleScene::render(void)
{
	_bg->render(getMemDC());
	_gameName->render(getMemDC());
	_start->frameRender(getMemDC(), _startRc.left, _startRc.top);
	_exit->frameRender(getMemDC(), _exitRc.left, _exitRc.top);
	if (changeScreenAlpha > 0) { _changeScreen->alphaRender(getMemDC(), changeScreenAlpha); }
}

#include "Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
	_bg = IMAGEMANAGER->addImage("EndImage", "Resource/Images/Lucie/CompleteImg/pitures/end.bmp", 960, 540);
	_changeScreen = IMAGEMANAGER->addImage("EndingBlackScreen", "Resource/Images/Lucie/CompleteImg/effect/changeScreen.bmp", 1104, 960);
	_titleChangeScreen = IMAGEMANAGER->addImage("ChangeTitleBlackScreen", "Resource/Images/Lucie/CompleteImg/effect/changeScreen.bmp", 1104, 960);
	
	_endChangeScreenAlpha = 255.0f;
	_titleChangeScreenAlpha = 0.0f;

	_changeSceneTime = TIMEMANAGER->getWorldTime();

	return S_OK;

}

void EndingScene::release(void)
{

}

void EndingScene::update(void)
{
	_endChangeScreenAlpha -= 3.0f;
	if (_endChangeScreenAlpha < 0.0f)
	{
		_endChangeScreenAlpha = 0.0f;
	}

	
	if (_endChangeScreenAlpha == 0.0f)
	{
		_endChangeScreenAlpha = 0.0f;
		
		if (TIMEMANAGER->getWorldTime() > _changeSceneTime + RATE_TIME)
		{
			_titleChangeScreenAlpha += 3.0f;

			if (_titleChangeScreenAlpha > 255.0f)
			{
				_titleChangeScreenAlpha = 0.0f;
				SCENEMANAGER->changeScene("TitleScene");
			}
		}
	}
}

void EndingScene::render(void)
{
	_bg->render(getMemDC());
	if (_endChangeScreenAlpha > 0) 
	{ 
		_changeScreen->alphaRender(getMemDC(), _endChangeScreenAlpha); 
	}

	if (_titleChangeScreenAlpha < 255.0f)
	{
		_titleChangeScreen->alphaRender(getMemDC(), _titleChangeScreenAlpha);
	}
}

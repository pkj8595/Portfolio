#include "Stdafx.h"
#include "Lobby.h"
#include "TextSystemManager.h"

HRESULT Lobby::init(void)
{
	

	_lobbyMapImg = IMAGEMANAGER->addImage("Lobby", "Resource/Images/Lucie/CompleteImg/ground/map/ground12.bmp", 1008, 1065);
	_lobbyColMapImg = IMAGEMANAGER->addImage("col_Lobby", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m12_1.bmp", 1008, 1065);
	_WhitefadeOutImg = IMAGEMANAGER->addImage("WhiteScreen", "Resource/Images/Lucie/CompleteImg/effect/BookchangeScreen.bmp", 1104, 960);
	_BlackfadeOutImg = IMAGEMANAGER->addImage("BlackScreen", "Resource/Images/Lucie/CompleteImg/effect/changeScreen.bmp", 1104, 960);
	_bookImg = IMAGEMANAGER->addFrameImage("Book", "Resource/Images/Lucie/CompleteImg/1stScene/diary_open.bmp", 384, 36, 8, 1, true, RGB(255, 0, 255));
	
	_player = new LobbyPlayer;
	_player->init();

	_basePt = PointMake(500, 280);

	_lobbyMap_rc = RectMake(0 - 50, 0 - 200, _lobbyMapImg->getWidth(), _lobbyMapImg->getHeight());
	_lobbyColMap_rc = RectMake(CAMERAMANAGER->getCameraRect().left - 50, CAMERAMANAGER->getCameraRect().top - 200, _lobbyColMapImg->getWidth(), _lobbyColMapImg->getHeight());
	_Imgbook_rc = RectMake(_basePt.x - 70, _basePt.y + 40, _bookImg->getFrameWidth(), _bookImg->getFrameHeight());
	_book_rc = RectMake(_basePt.x - 60, _basePt.y + 80, 30, 30);
	_box_rc = RectMake(_basePt.x - 240, _basePt.y + 30, 50, 80);
	_closet_rc = RectMake(_basePt.x + 75, _basePt.y - 50, 70, 50);
	_mirror_rc = RectMake(_basePt.x - 70, _basePt.y - 50, 40, 20);
	_window_rc = RectMake(_basePt.x - 140, _basePt.y - 50, 40, 20);
	_door_rc = RectMake(_basePt.x - 210, _basePt.y - 50, 40, 20);

	_tsm = new TextSystemManager;
	_tsm->init();

	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_frameSpeed = 0.1f;
	_fadeOutWhiteAlpha = 0;
	_fadeOutBlackAlpha = 0;
	_startAlpha = 255.0f;

	_tsm->iscollBox = false;
	_isbookOpen = false;
	return S_OK;
}

void Lobby::release(void)
{
	_tsm->release();
	SAFE_DELETE(_tsm);
	_player->release();
	SAFE_DELETE(_player);

}

void Lobby::update(void)
{
	_startAlpha -= 3.0f;

	if (_startAlpha < 0.0f)
	{
		_startAlpha = 0.0f;
	}

	if (_fadeOutWhiteAlpha > 252)
	{
		_fadeOutWhiteAlpha = 252;
		_fadeOutBlackAlpha += 3.0f;
	}
	if (_fadeOutBlackAlpha > 252)
	{
		_fadeOutBlackAlpha = 252;
		SCENEMANAGER->changeScene("PlayScene");
	}

	_tsm->update();
	_player->update();

	if (_isbookOpen) 
	{ 
		animation();
	}
	LobbyCollision();
}

void Lobby::render(void)
{
	IMAGEMANAGER->render("Lobby", getMemDC(), _lobbyMap_rc.left, _lobbyMap_rc.top);

	_bookImg->frameRender(getMemDC(),_Imgbook_rc.left, _Imgbook_rc.top, _bookImg->getFrameX(), _bookImg->getFrameY());
	
	_player->render();
	Collision();
	if (_fadeOutWhiteAlpha > 0) { _WhitefadeOutImg->alphaRender(getMemDC(), _fadeOutWhiteAlpha); }
	if (_fadeOutBlackAlpha > 0) { _BlackfadeOutImg->alphaRender(getMemDC(), _fadeOutBlackAlpha); }
	if (_startAlpha > 0) { _BlackfadeOutImg->alphaRender(getMemDC(), _startAlpha); }

	if (_isbookOpen) 
	{ 
		animation(); 
	}
}

void Lobby::animation(void)
{
	if (_frameSpeed + _worldTimeCount <= TIMEMANAGER->getWorldTime())
	{
		_worldTimeCount = TIMEMANAGER->getWorldTime();
		_index++;

		if (_index > _bookImg->getMaxFrameX())
		{
			_index = 4;
		}
		_bookImg->setFrameX(_index);
	}
}

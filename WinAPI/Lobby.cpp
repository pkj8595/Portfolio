#include "Stdafx.h"
#include "Lobby.h"
#include "TextSystemManager.h"

HRESULT Lobby::init(void)
{
	IMAGEMANAGER->addImage("Lobby", "Resource/Images/Lucie/CompleteImg/ground/map/ground12.bmp", 1008, 1065);
	IMAGEMANAGER->addImage("col_Lobby", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m12_1.bmp", 1008, 1065);
	_player = new Player;
	_player->init();
	_book_rc = RectMake(CENTER_X - 60, CENTER_Y + 70, 30, 30);
	_box_rc = RectMake(CENTER_X - 240, CENTER_Y, 50, 100);
	_closet_rc = RectMake(CENTER_X + 75, CENTER_Y - 50, 70, 50);
	_mirror_rc = RectMake(CENTER_X - 70, CENTER_Y - 50, 40, 20);
	_window_rc = RectMake(CENTER_X - 140, CENTER_Y - 50, 40, 20);
	_door_rc = RectMake(CENTER_X - 210, CENTER_Y - 50, 40, 20);

	_tsm = new TextSystemManager;
	_tsm->init();

	collBox = false;
	return S_OK;
}

void Lobby::release(void)
{
	_tsm->release();
	_player->release();
	SAFE_DELETE(_player);
}

void Lobby::update(void)
{
	_tsm->update();
	_player->update();

	LobbyCollision();
}

void Lobby::render(void)
{
	IMAGEMANAGER->render("Lobby", getMemDC());
	
	if (collision(_book_rc) && collBox) _tsm->EventLog(0);
	if (collision(_box_rc) && collBox) _tsm->EventLog(0);
	
	_player->render();

}

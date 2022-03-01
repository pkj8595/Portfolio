#include "Stdafx.h"
#include "Lobby.h"

void Lobby::Collision(void)
{
	//충돌 검사 -> Weapon Box와 충돌했을때
	if (IntersectRect(&rc, &_player->getRect(), &_box_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			//TextManager-> shopLog collBox bool true
			_tsm->iscollBox = true;
			_tsm->isShowText = true;
			_player->_isTextShow = true;
		}
		if (_tsm->iscollBox) { _tsm->EventLog(0); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_closet_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_tsm->isShowText = true;
			_player->_isTextShow = true;
		}
		//if (_tsm->iscollBox) { _tsm->EventLog(1); }
		if (_tsm->isShowText) { _tsm->ShopLog("로브", "탁월한 안감을 자랑하는 로브", 250); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_mirror_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_tsm->isShowText = true;
			_player->_isTextShow = true;
		}
		if (_tsm->isShowText) { _tsm->EventLog(2); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_window_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_tsm->isShowText = true;
			_player->_isTextShow = true;
		}
		if (_tsm->isShowText) { _tsm->EventLog(3); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_door_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_tsm->isShowText = true;
			_player->_isTextShow = true;
		}
		if (_tsm->isShowText) { _tsm->EventLog(4); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_book_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_bookOpen = true;
			_player->_isTextShow = true;
		}
		if (_bookOpen) { _fadeOutWhiteAlpha += 3.0f; }
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_tsm->isShowText = false;
		_tsm->iscollBox = false;
		_tsm->isShopcol = false;
		_player->_isTextShow = false;
	}
}


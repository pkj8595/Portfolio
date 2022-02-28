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
			_collBox = true;
			_tsm->iscollText = true;
			_tsm->iscollBox = true;
			_player->_isTextShow = true;
		}
		if (_collBox) { _tsm->EventLog(0); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_closet_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (_collBox) { _tsm->ShopLog(L"로브", L"좋은 원단으로 만든 옷이야", L"250"); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_mirror_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (_collBox) { _tsm->EventLog(2); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_window_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (_collBox) { _tsm->EventLog(3); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_door_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (_collBox) { _tsm->EventLog(4); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_book_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_bookOpen = true;
			_collBox = true;
		}
		if (_collBox) { _fadeOutWhiteAlpha += 3.0f; }
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_collBox = false;
		_tsm->iscollText = false;
		_player->_isTextShow = false;
	}
}


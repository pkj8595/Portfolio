#include "Stdafx.h"
#include "Lobby.h"

void Lobby::Collision(void)
{
	

	if (IntersectRect(&rc, &_player->getRect(), &_box_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (collBox) { _tsm->EventLog(0); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_closet_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (collBox) { _tsm->EventLog(1); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_mirror_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (collBox) { _tsm->EventLog(2); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_window_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (collBox) { _tsm->EventLog(3); }
	}

	else if (IntersectRect(&rc, &_player->getRect(), &_door_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;
		}
		if (collBox) { _tsm->EventLog(4); }
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		collBox = false;
		_tsm->iscollText = false;
		_player->_isTextShow = false;
	}
}


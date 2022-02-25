#include "Stdafx.h"
#include "Lobby.h"

bool Lobby::collision(RECT col_rc)
{
	if (IntersectRect(&rc, &_player->getRect(), &col_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			collBox = true;
			_tsm->iscollText = true;
			_player->_isTextShow = true;

			return true;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		collBox = false;
		_tsm->iscollText = false;
		_player->_isTextShow = false;
	}

	return true;
}


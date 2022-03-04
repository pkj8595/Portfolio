#include "Stdafx.h"
#include "Lobby.h"

void Lobby::Collision(void)
{
	//충돌 검사 -> Weapon Box와 충돌했을때
	if (IntersectRect(&_collision_rc, &_player->getRect(), &_box_rc))
	{
		if (!_tsm->isShowText)
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				//TextManager-> shopLog collBox bool true
				_tsm->iscollBox = true;
				_tsm->isEventOpen = true;
				_tsm->isShowText = true;
				_player->setisShowText(true);
			}
		}
		else
		{
			if (_tsm->iscollBox) { _tsm->EventLog(0); }
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = false;
				_tsm->isEventOpen = false;
				_tsm->iscollBox = false;
				_tsm->isShopCol = false;
			}
		}
		
	}

	else if (IntersectRect(&_collision_rc, &_player->getRect(), &_closet_rc))
	{
		if (!_tsm->isShowText)
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = true;
				_tsm->isEventOpen = true;
				_player->setisShowText(true);
			}
		}
		else
		{
			if (_tsm->isShowText) { _tsm->EventLog(1); }
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = false;
				_tsm->isEventOpen = false;
				_tsm->iscollBox = false;
				_tsm->isShopCol = false;
			}
		}
		
	}

	else if (IntersectRect(&_collision_rc, &_player->getRect(), &_mirror_rc))
	{
		if (!_tsm->isShowText)
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = true;
				_tsm->isEventOpen = true;
				_player->setisShowText(true);
			}
		}
		else
		{
			if (_tsm->isShowText) { _tsm->EventLog(2); }
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = false;
				_tsm->isEventOpen = false;
				_tsm->iscollBox = false;
				_tsm->isShopCol = false;
			}
		}
		
	}

	else if (IntersectRect(&_collision_rc, &_player->getRect(), &_window_rc))
	{
		if (!_tsm->isShowText)
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = true;
				_tsm->isEventOpen = true;
				_player->setisShowText(true);
			}
		}
		else
		{
			if (_tsm->isShowText) { _tsm->EventLog(3); }
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = false;
				_tsm->isEventOpen = false;
				_tsm->iscollBox = false;
				_tsm->isShopCol = false;
			}
		}
		
	}

	else if (IntersectRect(&_collision_rc, &_player->getRect(), &_door_rc))
	{
		if (!_tsm->isShowText)
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = true;
				_tsm->isEventOpen = true;
				_player->setisShowText(true);
			}
		}
		else
		{
			if (_tsm->isShowText) { _tsm->EventLog(4); }
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_tsm->isShowText = false;
				_tsm->isEventOpen = false;
				_tsm->iscollBox = false;
				_tsm->isShopCol = false;
			}
		}
	}

	else if (IntersectRect(&_collision_rc, &_player->getRect(), &_book_rc))
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_isbookOpen = true;
			_player->setisShowText(true);
			TEMPSOUNDMANAGER->playEffectSoundWave("Resource/Sound/Lucie/bookflip.wav");
		}
		if (_isbookOpen) { _fadeOutWhiteAlpha += 3.0f; }
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_tsm->isShowText = false;
		_tsm->isEventOpen = false;
		_tsm->iscollBox = false;
		_tsm->isShopCol = false;
	}

	if (!_tsm->isShowText)
	{
		_player->setisShowText(false);
	}
}


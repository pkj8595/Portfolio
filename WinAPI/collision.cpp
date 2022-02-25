#include "Stdafx.h"
#include "Lobby.h"

void Lobby::collision(void)
{
	RECT rc;
	if (IntersectRect(&rc, &_p_rc, &_Boxrc) && KEYMANAGER->isOnceKeyDown('E'))
	{
		collBox = true;
		_tsm->test = true;
	}
	else if (!IntersectRect(&rc, &_p_rc, &_Boxrc)) collBox = false;

	if (!collBox) _tsm->test = false;
}
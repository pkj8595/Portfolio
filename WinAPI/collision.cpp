#include "Stdafx.h"
#include "Lobby.h"

void Lobby::collision(void)
{
	RECT rc;
	if (IntersectRect(&rc, &_p_rc, &_Boxrc) && KEYMANAGER->isOnceKeyDown('E'))
	{
		collBox = true;
	}
	else if (!IntersectRect(&rc, &_p_rc, &_Boxrc)) collBox = false;
}
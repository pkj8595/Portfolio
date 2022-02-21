#include "Stdafx.h"
#include "ItemClass.h"

void Player_Skill::init(void)
{
	RECTOBSERVERMANAGER->registerObserved(this);
}

void Player_Skill::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
}

STObservedData Player_Skill::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &rc;
	temp.typeKey = &_type;
	temp.isActive = &_isActive;
	return temp;
}

void Player_Skill::collideObject()
{
	//todo
}

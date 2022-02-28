#include "Stdafx.h"
#include "EventObject.h"

void EventObject::init(EventObservedType typeKey, RECT rc, bool isActive, int num)
{
	_typeKey = typeKey;
	_rc = rc;
	_isActive = isActive;
	_num = num;
	RECTOBSERVERMANAGER->registerEventObserved(this);
}

void EventObject::release(void)
{
	RECTOBSERVERMANAGER->removeEventObserved(this);
}

STEventObservedData EventObject::getEventUpdate()
{
	STEventObservedData temp;
	temp.typeKey = &_typeKey;
	temp.rc = &_rc;
	temp.isActive = &_isActive;
	temp.num = &_num;
	return temp;
}

void EventObject::collideEventObject(STEventObservedData obEventData)
{
}

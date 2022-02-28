#include "Stdafx.h"
#include "EventObject.h"

void EventObject::init(EventObservedType typeKey, RECT rc, bool isActive)
{
	_typeKey = typeKey;
	_rc = rc;
	_isActive = isActive;
}

void EventObject::release(void)
{

}

STEventObservedData EventObject::getEventUpdate()
{
	STEventObservedData temp;
	temp.typeKey = &_typeKey;
	temp.rc = &_rc;
	temp.isActive = &_isActive;
	return STEventObservedData();
}

void EventObject::collideEventObject(STEventObservedData obEventData)
{
}

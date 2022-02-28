#pragma once
#include "IRectObserved.h"


class EventObject : public IEventObservered
{
public:
	EventObservedType _typeKey;
	RECT _rc;
	bool* _isActive;
	int _num;

	void init(EventObservedType typeKey, RECT rc, bool* isActive,int num);
	void release(void);
	void setIsActive(bool* isActive) { _isActive = isActive; }
	bool getIsActive() { return *_isActive; }

	virtual STEventObservedData getEventUpdate();
	virtual void collideEventObject(STEventObservedData obEventData);

	EventObject() {}
	~EventObject() {}
};
#pragma once
#include "IRectObserved.h"


class EventObject : public IEventObservered
{
public:
	EventObservedType _typeKey;
	RECT _rc;
	bool* _isMapActive;
	int _num;
	bool _isRemoveObserver;
	bool _isExcute;

	void init(EventObservedType typeKey, RECT rc, bool* isMapActive,int num);
	void release(void);
	void setIsActive(bool* isMapActive) { _isMapActive = isMapActive; }
	bool getIsActive() { return *_isMapActive; }

	void setIsExcute(bool isExcute) { _isExcute = isExcute; }
	bool getIsExcute() { return _isExcute; }

	bool getIsRemoveObserver()
	{
		return _isRemoveObserver;
	}

	virtual STEventObservedData getEventUpdate();
	virtual void collideEventObject(STEventObservedData obEventData);

	EventObject() {}
	~EventObject() {}
};
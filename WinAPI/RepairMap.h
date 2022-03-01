#pragma once
#include "Map.h"

class RepairMap : public Map
{
private:
	EventObject* _repairEventObj;
	RECT _repairEventRc;
	
public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
};


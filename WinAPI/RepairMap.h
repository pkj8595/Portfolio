#pragma once
#include "Map.h"

class RepairMap : public Map
{
private:
	my::Image* _anvilImage;
	int _frameY;

	EventObject* _repairEventObj;
	RECT _repairEventRc;
	
public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
};


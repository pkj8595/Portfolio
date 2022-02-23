#pragma once
#include "Map.h"
class StartMap : public Map
{
private:
	bool _pixel;
public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
};


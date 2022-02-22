#pragma once
#include "Map.h"

class ChestMap : public Map
{
private:

public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
};


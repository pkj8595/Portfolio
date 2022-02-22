#pragma once
#include "GameNode.h"
class Inventory : GameNode
{

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};


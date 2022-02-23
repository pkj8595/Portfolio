#pragma once
#include "GameNode.h"
#include "mButton.h"
class Inventory : public GameNode
{
	my::Image* _window;
	mButton* _btn;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};


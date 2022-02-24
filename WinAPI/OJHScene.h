#pragma once
#include "GameNode.h"

class OJHScene : public GameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	OJHScene() {}
	~OJHScene() {}
};
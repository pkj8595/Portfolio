#pragma once
#include "GameNode.h"
#include "TextSystemManager.h"

class OJHScene : public GameNode
{
private:
	TextSystemManager* _tsm;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	OJHScene() {}
	~OJHScene() {}
};
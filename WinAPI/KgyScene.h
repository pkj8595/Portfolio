#pragma once
#include "GameNode.h"
#include "EnemyManager.h"

class KgyScene:public GameNode
{
private:
	EnemyManager* _em;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	KgyScene();
	virtual ~KgyScene();
};


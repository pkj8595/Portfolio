#pragma once
#include "GameNode.h"
/*
���� �۾��ϴ� ���� �޶� 
���� play 
���� �� �۾� ���� 
���� �� OJHScene
���� �� pkjScene


*/

class MainGame : public GameNode
{
private:

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);		
	virtual void render(void);

	MainGame() {}
	virtual ~MainGame() {}
};
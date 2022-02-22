#pragma once
#include "GameNode.h"

/*
각자 작업하는 씬이 달라 
형우 play 
가연 씬 작업 ㄱㄱ 
재훈 씬 OJHScene
경재 씬 pkjScene


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
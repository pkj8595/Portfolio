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
	inline void addSounds(void);
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);		
	virtual void render(void);
	virtual void renderUI(void);
	

	MainGame() {}
	virtual ~MainGame() {}

};
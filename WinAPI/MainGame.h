#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	my::Image* _mouseImg;
	inline void addSounds(void);
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);		
	virtual void render(void);

	MainGame() {}
	virtual ~MainGame() {}
};
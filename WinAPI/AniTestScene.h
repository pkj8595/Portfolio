#pragma once
#include "GameNode.h"
#include "Animation.h"

class AniTestScene : public GameNode
{
private:
	my::Image* _image;
	Animation* _animationA;
public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	AniTestScene() {}
	~AniTestScene() {}
};


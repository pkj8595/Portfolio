#pragma once
#include "GameNode.h"
#include "CEffect.h"

class EffectManager: public GameNode
{
private:
	typedef vector<CEffect*> vEffect;
	typedef vector<CEffect*>::iterator viEffect;

private:
	vEffect _vEffect;
	viEffect _viEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void createEffect(const char* fileName,RECT rc);
	void createEffect(const char* fileName,RECT* rc);
	void createEffect(const char* fileName,RECT rc, float count);

	EffectManager() {}
	~EffectManager() {}
};


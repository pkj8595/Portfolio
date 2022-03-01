#pragma once
#include "GameNode.h"

struct skillParticle
{
	RECT rc;
	float x;
	float y;
	float angle;
	float speed;
	float disappearspeed;
	int alpha;
};
class SkillParticle : public GameNode
{
private:
	my::Image* _particle;

	vector<skillParticle> _vParticle;
	vector<skillParticle>::iterator _viParticle;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createParticle(float x, float y);
};


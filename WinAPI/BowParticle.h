#pragma once
#include "GameNode.h"

struct Particle
{
	RECT rc;
	float x;
	float y;
	float angle;
	float speed;
	float disappearspeed;
	int alpha;
};
class BowParticle : public GameNode
{
private:
	my::Image* _particle;

	vector<Particle> _vParticle;
	vector<Particle>::iterator _viParticle;

public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void createParticle(float x, float y);
};


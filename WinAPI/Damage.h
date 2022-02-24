#pragma once
#include "GameNode.h"

class Damage : public GameNode
{
private:
	my::Image* _image;
	RECT _rc;

	int _amount;		//
	int _type;
	float _x, _y;
	float _dy;

	int _showCount;

public:
	HRESULT init(int damage, bool isMagicDamage, float x, float y);
	void release(void);
	void update(void);
	void render(void);

	Damage() {}
	~Damage() {}

	bool isShow()
	{
		if (_showCount > 0) return true;
		else return false;
	}
};


#pragma once
#include "GameNode.h"
#include "ItemClass.h"

class PlayerStatusUI : public GameNode
{
private:
	my::Image* _layout;
	my::Image* _levelImage;
	my::Image* _hp;
	my::Image* _maxHp;
	my::Image* _mp;
	my::Image* _maxMp;
	my::Image* _exp;
	my::Image* _stamina;

	POINT _pos;
	CPlayer_Attribute* _status;
	int* _level;

	float _staminaWidth;
	float _expWidth;
public:
	HRESULT init(CPlayer_Attribute* status, int* level);
	void release(void);
	void update(void);
	void render(void);

	void hpRender(void);
	void mpRender(void);
};


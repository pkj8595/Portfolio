#pragma once
#include "iSkill.h"

class Reflection :public iSkill
{
private:

public:
	virtual void SkillTrigger(RECT rc) {};
	virtual void SkillUpdate() {};
	virtual void SkillRender(HDC hdc) {};

};


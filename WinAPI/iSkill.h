#pragma once

class iSkill
{
private:

public:
	iSkill() {}
	virtual ~iSkill() {}

	virtual void SkillTrigger(RECT rc) = 0;
	virtual void SkillUpdate() = 0;
	virtual void SkillRender(HDC hdc) = 0;

};


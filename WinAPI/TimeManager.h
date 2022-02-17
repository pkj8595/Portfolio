#pragma once
#include "SingletonBase.h"
#include "Timer.h"

//게임노드와 별개 개체로 사용
class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* _timer;

public:
	HRESULT init(void);
	void release(void);
	void update(float lock = 0.0f);
	void render(HDC hdc);

	inline float getFrameRate(void)const { return _timer->getFrameRate(); }
	inline float getWorldTime(void)const { return _timer->getWorldTime(); }
	inline float getElapsedTime(void)const { return _timer->getElapsedTime(); }

	//굳이 전역인데 쓸필요없
	TimeManager() {}
	~TimeManager() {}
};


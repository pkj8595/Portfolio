#pragma once

class Timer
{
private:
	float _timeScale;		//경과시간
	float _timeElapsed;		//마지막 시간과 현재시간의 경과값
	bool _isHardware;		//고성능 타이머 지원 여부

	__int64 _curTime;			//현재 시간
	__int64 _lastTime;			//이전 시간
	__int64 _periodFrequency;	//시간주기

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init(void);
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = nullptr) const;
	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }

	Timer() {}
	~Timer() {}
};


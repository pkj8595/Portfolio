#pragma once

class Timer
{
private:
	float _timeScale;		//����ð�
	float _timeElapsed;		//������ �ð��� ����ð��� �����
	bool _isHardware;		//���� Ÿ�̸� ���� ����

	__int64 _curTime;			//���� �ð�
	__int64 _lastTime;			//���� �ð�
	__int64 _periodFrequency;	//�ð��ֱ�

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


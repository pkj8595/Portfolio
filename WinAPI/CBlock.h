#pragma once
#include "SimpleTranslate.h"

#define READY_COLOR		Color(100,255, 32, 100)
#define WHITE_COLOR		Color(180, 180, 180)
#define BASE_COLOR		Color(255, 32, 113)

enum blockDrection 
{
	LEFT=0,
	TOP,
	RIGHT,
	BOTTOM,
	POSITION
};

class CBlock :public SimpleTranslate 
{
private:
	RECT _outRc;

	Gdiplus::RectF _rc;
	string _imgKey;
	int _time;
	int _activeTime;
	int _whiteTime;
	int _timeOffset;
	bool _isFlash;
	bool _isExecuteFlash;
	bool _isActive;
	bool _isPen;
	bool _isReadyPosition;
	bool _isFlashReady;
	bool _isRandomOffsetTime;
	float _size;
	float _addAngle;
	float _angle;
	REAL _penWidth;
	INT _speed;
	blockDrection _drection;

	typedef struct tagDirection
	{
		int xDir;
		int yDir;
	}ST_Dir;
	ST_Dir _dir;

public:
	

	void setResetRc(RectF rc, INT speed, bool ispen,REAL penWidth,int timeoffset, blockDrection drec);
	void setResetImg(string key,float size,INT speed, int timeoffset, blockDrection drec);
	void ResetPositionRc(RectF rc, REAL x, REAL y, INT whiteTime, bool ispen, REAL penWidth,DWORD time, int timeoffset, int activeTime, float addAngle);

	Gdiplus::RectF getRect() { return _rc; }
	INT getSpeed() { return _speed; }
	int getTime() { return _time; }
	float getSize() { return _size; }
	bool getIsActive() { return _isActive; }
	int getTimeOffset() { return _timeOffset; }
	REAL getPenWidth() { return _penWidth; }
	float getLocalAngle() { return _angle; }
	bool getIsReadyPosition() { return _isReadyPosition; }
	ST_Dir getDirection() { return _dir; }

	void addDirectionX() { _dir.xDir++; }
	void addDirectionY() { _dir.yDir++; }
	void setSpeed(INT speed) { _speed = speed; }
	void setRect(Gdiplus::RectF rc) { _rc = rc; }
	void setImageKey(string imgKey) { _imgKey = imgKey; }
	void setTime(int time) { _time = time; }
	void setSize(float size) { _size = size; }
	void setIsActive(bool isActive) { _isActive = isActive; _activeTime = 0; }
	void setPenWidth(REAL w) { _penWidth = w; }
	void setDreaction(blockDrection w) { _drection = w; }
	void setAddAngle(float angle) { _addAngle = angle; }
	void setIsFrash(bool isFlash) { _isFlash = isFlash; }
	void setActiveTime(int time) { _activeTime = time; }
	void setLocalAngle(float angle) { _angle = angle; }
	void setTimeOffset(int time) { _timeOffset = time; }
	void setWhiteTime(int time) { _whiteTime = time; }
	void setIsRandomTime(bool isRandomTime) { _isRandomOffsetTime = isRandomTime; }
	void setIsReadyPosition(bool isReadyPosition) {
		_isReadyPosition = isReadyPosition;}

	void update(int time);
	void render(Gdiplus::Graphics *g);

	CBlock();
	CBlock(int time, float size=4) {
		_size = size;
		_time = time;
	}
	~CBlock() 
	{ 
	}
};


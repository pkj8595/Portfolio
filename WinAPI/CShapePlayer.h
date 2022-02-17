#pragma once

#define PARTCLE_SIZE	15
#define DASHELL_SIZE	5


class CShapePlayer
{
private:
	struct tagParticle 
	{
		Gdiplus::Rect rc;
		int alpha;
		bool isActive;

		tagParticle() 
		{
			rc = Rect(0, 0, 8, 8);
			alpha = 255;
			isActive = false;
		}
	};

	struct tagDashEll
	{
		Gdiplus::Rect	dashEll;
		Gdiplus::Color	color;
		Gdiplus::Point	pt;
		INT penWidth;
		INT radius;
		int alpha;
		bool isActive;

		tagDashEll() 
		{
			dashEll = Rect(0, 0, 0, 0);
			color = Color(0, 0, 0, 0);
			penWidth = 5;
			radius = 20;
			alpha = 255;
			isActive = false;
		}
	};
	
	Gdiplus::Matrix	_mPlayer;
	Gdiplus::RectF _rc;
	Gdiplus::RectF _dashRc;
	string _imgKey;

	tagDashEll	_dashEll[DASHELL_SIZE];
	tagParticle _partcle[PARTCLE_SIZE];
	POINT _pt;
	POINT _previousPt;
	float _angle;
	long _dashTime;
	long _beAttackedTime;
	int _dashSpeed;
	int _speed;
	int _maxHp;
	int _hp;
	INT _mapSpeed;
	bool _isMove;
	bool _isDash;
	bool _isBeAttacked;

public:
	RectF getRC() { return _rc; }
	RectF getDashRC() { return _dashRc; }
	int getHp() { return _hp; }
	int getSpeed() { return _speed; }
	float getAngle() { return _angle; }
	POINT getPoint() { return _pt; }

	void setRC(RectF rc) { _rc = rc; }
	void setSpeed(int speed) { _speed = speed; }
	void setHp(int hp) { _hp = hp; }
	void setMaxHp(int maxhp) { _maxHp = maxhp; }
	void setPoint(long x, long y) { _pt = POINT{ x,y }; }
	void beAttacked(long time);

	void update(int time);
	void render(Gdiplus::Graphics *g);

	CShapePlayer();
	~CShapePlayer() {}
};


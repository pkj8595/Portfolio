#pragma once

struct tagCannon {
	POINT center;
	POINT cannonEnd;
	float angle;
	float cannonAngleStart;
	float cannonAngleEnd;
	int radius;
	int length;
	bool dir;				//증감
};

struct tagBullet
{
	RECT rc;
	bool isFire;
	float angle;
};

class HomeWork_0107_1 : public Scene_inter
{
private:

	tagCannon _cannon;
	tagBullet _bullet[60];
	int _count;

	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);	//삼각함수는 update가 중요	
	virtual void render(HDC hdc);

	void fire(void);

	HomeWork_0107_1() {}
	virtual ~HomeWork_0107_1() {}
};


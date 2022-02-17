#pragma once

#define RECT_SIZE		100
#define ELL_SIZE		100

enum SHAPE 
{
	NULL_SHAPE,
	RECT_SHAPE,
	ELLIPSE_SHAPE
};

class HomeWork_0111 :public Scene_inter
{
private:
	SHAPE _selectedShape;

	RECT  _rc;
	float _rcCrossDistance;

	POINT _ellpt;

	POINT _previousMousePt;		//마우스의 이전 좌표
	float _mouseSpeed;			
	float _mouseAngle;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	bool PtInCircle(POINT &circlePt, float round, POINT pt);
};


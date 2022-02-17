#include "Stdafx.h"
#include "rotateRect.h"

HRESULT rotateRect::init(void)
{
	_radian = 3.141592643f;
	_degree = 180.0f;

	for (int i = 0; i <= 5; ++i)
	{
		_star[i].x = cosf((i * 72 - 90)*PI / 180.0f) * 200 + WINSIZE_X / 2;
		_star[i].y = sinf((i * 72 - 90)*PI / 180.0f) * 200 + WINSIZE_Y / 2;
	}
	/*
	1. 오망성을 그리기 위해서는 5개의 포인트가 필요하다. -> 72는 360/5
	2. -90는 초기 시작 각도
	3. 디그리를 라디안으로 고처주기위해 (1degree == PI / 180 radian)
	4. 200 중점에서의 거리
	5. winsize_x/2 중점
	*/



	_h.x = cosf((-90)*PI / 180.0f) * 150 + WINSIZE_X / 2;
	_h.y = sinf((-90)*PI / 180.0f) * 150 + WINSIZE_Y / 2;

	_m.x = cosf((-90)*PI / 180.0f) * 200 + WINSIZE_X / 2;
	_m.y = sinf((-90)*PI / 180.0f) * 200 + WINSIZE_Y / 2;

	_s.x = cosf((-90)*PI / 180.0f) * 180 + WINSIZE_X / 2;
	_s.y = sinf((-90)*PI / 180.0f) * 180 + WINSIZE_Y / 2;

	for (int i = 0; i < 12; i++)
	{
		_clockText[i].x = cosf((i * 30 - 90) * PI / 180.0f) * (200 / 2) + WINSIZE_X / 2;
		_clockText[i].y = sinf((i * 30 - 90) * PI / 180.0f) * (200 / 2) + WINSIZE_Y / 2;
	}

	_rc = RectMakeCenter(WINSIZE_X*0.75f, WINSIZE_Y*0.75f, 100, 100);
	_rcPoint.x = WINSIZE_X * 0.75f;
	_rcPoint.y = WINSIZE_Y * 0.75f;

	_roRcPoint.x = WINSIZE_X * 0.25f;
	_roRcPoint.y = WINSIZE_Y * 0.75f;

	_count = 0;
	_rcDegree = 0;

	x1 = 100;
	y1 = 100;
	x2 = -100;
	y2 = -100;
	z1 = WINSIZE_X / 2;
	z2 = WINSIZE_Y / 2;
	r1 = sqrt((x1*x1) + (y1*y1));
	r2 = sqrt((x2*x2) + (y2*y2));

	_roRect0111 = RectMakeCenter(200,200,100,100);
	_angle0111 = PI/2;
	_roPt0111 = PointMake(0, 0);

	xDir = true;
	yDir = true;

	return S_OK;
}

void rotateRect::release(void)
{
}

void rotateRect::update(void)
{
	GetLocalTime(&_st);
	_st.wSecond;	//달, 월, 일, 초,분,밀리세컨까지 다 가져올수 있음 os에서의 시간을 가져오는 친구
	_st.wHour;

	/*
	h = 360 / 12
	m = 360 / 60
	s = 360 / 60
	*/

	_h.x = cosf(((_st.wHour * 30) - 90)*PI / 180.0f) * (100 / 2) + WINSIZE_X / 2;
	_h.y = sinf(((_st.wHour * 30) - 90)*PI / 180.0f) * (100 / 2) + WINSIZE_Y / 2;

	_m.x = cosf(((_st.wMinute * 6) - 90)*PI / 180.0f) * (200 / 2) + WINSIZE_X / 2;
	_m.y = sinf(((_st.wMinute * 6) - 90)*PI / 180.0f) * (200 / 2) + WINSIZE_Y / 2;

	_s.x = cosf(((_st.wSecond * 6) - 90)*PI / 180.0f) * (180 / 2) + WINSIZE_X / 2;
	_s.y = sinf(((_st.wSecond * 6) - 90)*PI / 180.0f) * (180 / 2) + WINSIZE_Y / 2;

	_count++;
	/*
	_rc.left = (cosf((1 + 90) * PI / 180.0f)) *(100 / 2) + _rcPoint.x;
	_rc.top = -(sinf((1 - 90) * PI / 180.0f)) *(100 / 2) + _rcPoint.y;

	_rc.right = -(cosf((1 - 90) * PI / 180.0f)) *(100 / 2) + _rcPoint.x;
	_rc.bottom = (sinf((1 + 90) * PI / 180.0f)) *(100 / 2) + _rcPoint.y;
	*/

	/*
	//
	_rc.left = (cosf((_count) * PI / 180.0f)) *(100 / 2) + _rcPoint.x;
	_rc.top = (sinf((_count - 90) * PI / 180.0f)) *(100 / 2) + _rcPoint.y;

	_rc.right = (cosf((_count +90) * PI / 180.0f)) *(100 / 2) + _rcPoint.x;
	_rc.bottom = (sinf((_count ) * PI / 180.0f)) *(100 / 2) + _rcPoint.y;
	*/


	_rc.left = (cosf((_count)* PI / 180.0f)) *(100 / 2) + _rcPoint.x;
	_rc.top = (sinf((_count - 90) * PI / 180.0f)) *(100 / 2) + _rcPoint.y;

	_rc.right = (cosf((_count + 90) * PI / 180.0f)) *(100 / 2) + _rcPoint.x;
	_rc.bottom = (sinf((_count)* PI / 180.0f)) *(100 / 2) + _rcPoint.y;

	/*
		방향벡터 : sin,cos이 방향벡터..
		(x/r) (y/r)		반지름 100 , x :
	*/
	/*
	directionVector.x = (cosf((_count)* PI / 180.0f))*100;
	directionVector.y = (sinf((_count)* PI / 180.0f))*100;
	*/
	// y : 200	x: 100  >> sqrt(x^2 + y^2) 반지름을 기준으로 돈다.
	directionVector.x = (30 * cosf((_count)* PI / 180.0f)) + (30 * sinf((_count)* PI / 180.0f));
	directionVector.y = (30 * -sinf((_count)* PI / 180.0f)) - (30 * cosf((_count)* PI / 180.0f));

	directionVector2.x = (50 * cosf((_count)* PI / 180.0f)) + (50 * sinf((_count)* PI / 180.0f));
	directionVector2.y = (50 * -sinf((_count)* PI / 180.0f)) + (50 * cosf((_count)* PI / 180.0f));


	rP.x = cosf(((xDir ? 0 : 180)+(_count))* PI / 180.0f) * 200 + 400;
	rP.y = -sinf(((yDir ? 0 : 180)+(_count))* PI / 180.0f) * 200 + 400;

	//사각형 돌리기 ========================================
	/*
	2차원 사각형 돌리기 
	중심점 필요 

	
	*/
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		//_rcDegree -= 5;
		_angle0111 += 0.01f;
		_roPt0111.x -= 10;

	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		//_roRcPoint.y += 5;
		//_rc.left /= sqrt(100 / 2);
		_roPt0111.y -= 20;

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		//_rcDegree -= 5;
		_angle0111 -= 0.01f;
		_roPt0111.x += 10;


	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_roPt0111.y += 20;

		//_roRcPoint.y += 5;
		//_rc.left /= sqrt(100 / 2);
	}
	
	/*_roPt0111.x = (_roRect0111.left + _roRect0111.right) / 2;
	_roPt0111.y = (_roRect0111.top + _roRect0111.bottom) / 2;
	_roRect0111.left = (cosf(_angle0111* (PI / 180.0f))* _roRect0111.left) - (sinf(_angle0111* (PI / 180.0f))*_roRect0111.top) + _roPt0111.x;
	_roRect0111.top = (sinf(_angle0111* (PI / 180.0f))*_roRect0111.left) + (cosf(_angle0111* (PI / 180.0f)) *_roRect0111.top) + _roPt0111.x;
	_roRect0111.right = (cosf(_angle0111* (PI / 180.0f))* _roRect0111.right) - (sinf(_angle0111* (PI / 180.0f))*_roRect0111.bottom) + _roPt0111.y;
	_roRect0111.bottom = (sinf(_angle0111* (PI / 180.0f))*_roRect0111.right) + (cosf(_angle0111* (PI / 180.0f)) *_roRect0111.bottom) + _roPt0111.y;
*/


	//====================================================
	//====================================================
	//====================================================
	_roRect.left = (-100 * cosf((_count)* PI / 180.0f)) - (-100 * sinf((_count)* PI / 180.0f)) + rP.x;
	_roRect.top = (-100 * sinf((_count)* PI / 180.0f)) + (-100 * cosf((_count)* PI / 180.0f)) + rP.y;

	_roRect.right = (100 * cosf((_count)* PI / 180.0f)) - (100 * sinf((_count)* PI / 180.0f)) + rP.x;
	_roRect.bottom = (100 * sinf((_count)* PI / 180.0f)) + (100 * cosf((_count)* PI / 180.0f)) + rP.y;


	//_roRect.left = (-100*rP.x) - (-100 * rP.y)+ rP.x;
	//_roRect.top = (-100 * rP.x) + (-100 * rP.y)+ rP.y;

	//_roRect.right = (100*rP.x) - (100*rP.y)+ rP.x;
	//_roRect.bottom = (100 * rP.x) + (100*rP.y)+ rP.y;



	// x1 = 100 , y1 = 100
	// x2 = -100 , y2 = -100


/*
	_roRect.left = (x1*(y1/r1))+(y1*(x1/r1))+z1;
	_roRect.top = ((-2*x1)/r1)+((2*y1)/r1)+z1;

	_roRect.right = (x2*((y2) / r2)) + (y2*((x2) / r2)) + z2;
	_roRect.bottom = ((-2 * x2) / r2) + ((2 * y2) / r2) + z2;*/

	//======================================


	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		//_roRcPoint.y -= 5;
		if (yDir)
		{
			yDir = false;
		}
		else {
			yDir = true;
		}
	}

	

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (xDir) 
		{
			xDir = false;
		}
		else {
			xDir = true;
		}
		//_rcDegree += 5;
	}

	

	RotateLineMake(_roRcPoint, 100, _rcDegree);
}

void rotateRect::render(HDC hdc)
{
	char strRadian[128];
	char strDegree[128];
	char strSecond[128];

	sprintf_s(strSecond, "%d초", _st.wSecond);
	TextOut(hdc, WINSIZE_X / 2 + 200, WINSIZE_Y / 2 - 50, strSecond, strlen(strSecond));

	/*HPEN mononPen = CreatePen(PS_DASH, 1, RGB(10,10,10));
	HPEN curMononPen = (HPEN)SelectObject(hdc, mononPen);
	for (int i = 0; i < 8; i++)
	{
		LineMake(hdc, 0, i * 100, WINSIZE_X, i * 100);
		LineMake(hdc, i * 100, 0 , i * 100, WINSIZE_Y);
	}
	DeleteObject(mononPen);*/



	sprintf_s(strRadian, "%.2f 라디안 값은 %.2f 디그리 값과 같다.",
		_radian, _radian * (180.0f / M_PI));
	TextOut(hdc, WINSIZE_X / 2 - 100, WINSIZE_Y / 2 - 100, strRadian, strlen(strRadian));

	sprintf_s(strDegree, "%.2f 디그리 값은 %.2f 라디안 값과 같다.", _degree, _degree *(PI / 180.0f));
	TextOut(hdc, WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200, strDegree,
		strlen(strDegree));

		/*오망성
		HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		HPEN currentPen;
		currentPen = (HPEN)SelectObject(hdc, pen);

		LineMake(hdc, _star[0].x, _star[0].y, _star[3].x, _star[3].y);
		LineMake(hdc, _star[1].x, _star[1].y, _star[3].x, _star[3].y);
		LineMake(hdc, _star[1].x, _star[1].y, _star[4].x, _star[4].y);
		LineMake(hdc, _star[2].x, _star[2].y, _star[4].x, _star[4].y);
		LineMake(hdc, _star[2].x, _star[2].y, _star[0].x, _star[0].y);

		DeleteObject(pen);
		*/

		/*
		x = cos
		y = sin

		0~90	:	x+ , y-
		90~180	:	x- , y-
		180~270	:	x- , y+
		270~360	:	x+ , y+

		각도에 90을 더한다.
		x = -cos(d+90)
		y = -sin(d+90)

		거리
		*/

		/*EllipseMakeCenter(hdc,WINSIZE_X / 2, WINSIZE_Y/2, 200, 200);

		HPEN penH = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		HPEN curPenH = (HPEN)SelectObject(hdc, penH);
		LineMake(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, _h.x, _h.y);
		DeleteObject(penH);

		HPEN penM = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		HPEN curPenM = (HPEN)SelectObject(hdc, penM);
		LineMake(hdc, WINSIZE_X / 2, WINSIZE_Y / 2,_m.x, _m.y);
		DeleteObject(penM);

		HPEN penS = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		HPEN curPenS = (HPEN)SelectObject(hdc, penS);
		LineMake(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, _s.x, _s.y);
		DeleteObject(penS);

		for (int i = 0; i < 12; i++)
		{
			char n[12][10];
			sprintf_s(n[i], "%d", i);
			TextOut(hdc, _clockText[i].x , _clockText[i].y, n[i], strlen(n[i]));
		}*/

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HPEN curPen = (HPEN)SelectObject(hdc, pen);
	Rectangle(hdc, _rc.left, _rc.top, _rc.right, _rc.bottom);

	LineMake(hdc, _roRc.p11.x, _roRc.p11.y, _roRc.p12.x, _roRc.p12.y);
	LineMake(hdc, _roRc.p12.x, _roRc.p12.y, _roRc.p22.x, _roRc.p22.y);
	LineMake(hdc, _roRc.p22.x, _roRc.p22.y, _roRc.p21.x, _roRc.p21.y);
	LineMake(hdc, _roRc.p21.x, _roRc.p21.y, _roRc.p11.x, _roRc.p11.y);





	Rectangle(hdc, directionVector.x + 400, directionVector.y + 400, directionVector2.x + 400, directionVector2.y + 400);
	LineMake(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, directionVector.x + WINSIZE_X / 2, directionVector.y + WINSIZE_Y / 2);
	LineMake(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, directionVector2.x + WINSIZE_X / 2, directionVector2.y + WINSIZE_Y / 2);
	char directionVectorText[128];
	sprintf_s(directionVectorText, "x : %d  y : %d ", directionVector.x, directionVector.y);
	TextOut(hdc, directionVector.x + 400, directionVector.y + 400, directionVectorText, strlen(directionVectorText));

	char directionVectorText2[128];
	sprintf_s(directionVectorText2, "x` : %d  y` : %d ", directionVector2.x, directionVector2.y);
	TextOut(hdc, directionVector2.x + 400, directionVector2.y + 400, directionVectorText2, strlen(directionVectorText2));

	Rectangle(hdc, _roRect.left, _roRect.top, _roRect.right, _roRect.bottom);

	LineMake(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, rP.x, rP.y);

	//====================================================
	HPEN mypen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HPEN mycurrentPen;
	mycurrentPen = (HPEN)SelectObject(hdc, mypen);
	RectangleMakeToRECT(hdc, _roRect0111);

	DeleteObject(mypen);




	//====================================================
	char roRcText1[128];
	sprintf_s(roRcText1, "p11");
	TextOut(hdc, _roRc.p11.x, _roRc.p11.y, roRcText1, strlen(roRcText1));

	sprintf_s(roRcText1, "p12");
	TextOut(hdc, _roRc.p12.x, _roRc.p12.y, roRcText1, strlen(roRcText1));

	sprintf_s(roRcText1, "p21");
	TextOut(hdc, _roRc.p21.x, _roRc.p21.y, roRcText1, strlen(roRcText1));

	sprintf_s(roRcText1, "p22");
	TextOut(hdc, _roRc.p22.x, _roRc.p22.y, roRcText1, strlen(roRcText1));

	char roRcText2[128];
	sprintf_s(roRcText2, "left : %d", _rc.left - _rcPoint.x);
	TextOut(hdc, _rc.left, _rc.top - 20, roRcText2, strlen(roRcText2));

	sprintf_s(roRcText2, "top : %d", _rc.top - _rcPoint.y);
	TextOut(hdc, _rc.left, _rc.top, roRcText2, strlen(roRcText2));

	sprintf_s(roRcText2, "right : %d", _rc.right - _rcPoint.x);
	TextOut(hdc, _rc.right, _rc.bottom - 20, roRcText2, strlen(roRcText2));

	sprintf_s(roRcText2, "bottom : %d", _rc.bottom - _rcPoint.y);
	TextOut(hdc, _rc.right, _rc.bottom, roRcText2, strlen(roRcText2));

	DeleteObject(pen);
}

void rotateRect::RotateLineMake(POINT point, float radius, float degree)
{
	_roRc.p11.x = cosf((degree - 90) * PI / 180.0f) *(radius / 2) + point.x;
	_roRc.p11.y = sinf((degree - 90) * PI / 180.0f) *(radius / 2) + point.y;

	_roRc.p12.x = cosf((degree)* PI / 180.0f) *(radius / 2) + point.x;
	_roRc.p12.y = sinf((degree)* PI / 180.0f) *(radius / 2) + point.y;

	_roRc.p22.x = cosf((degree + 90) * PI / 180.0f) *(radius / 2) + point.x;
	_roRc.p22.y = sinf((degree + 90) * PI / 180.0f) *(radius / 2) + point.y;

	_roRc.p21.x = cosf((degree + 180) * PI / 180.0f) *(radius / 2) + point.x;
	_roRc.p21.y = sinf((degree + 180) * PI / 180.0f) *(radius / 2) + point.y;
}

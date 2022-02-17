#pragma once

// 필요한 함수는 직접 만들어 추가

inline POINT PointMake(int  x, int y)
{
	POINT pt = {x, y};
	return pt;
}

inline void LineMake(HDC hdc,int startX,int startY,int endX,int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}
	
inline RECT RectMake(int x, int y, int width, int height) 
{
	//todo
	RECT rc = { x, y,x + width,y + height };
	return rc;
}

//RECT 중심점에 만들기
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2 , y - height / 2,x + width / 2 , y + height / 2 };
	return rc;

}

//사각형 그리기 

inline void RectangleMake(HDC hdc, int x, int y, int width, int height) 
{
	Rectangle(hdc,x, y, x + width, y + height);
}

inline void RectangleMakeToRECT(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}


inline void EllipsMake(HDC hdc, int x, int y, int width, int height) 
{
	Ellipse(hdc, x, y, x + width, y + width);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height) 
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}


inline bool RectCollider(RECT rcA, RECT rcB)
{
	if (rcA.left <= rcB.right  &&
		rcA.top <= rcB.bottom &&
		rcA.right >= rcB.left &&
		rcA.bottom >= rcB.top)
	{
		return true;
	}
	return false;
}


inline bool RectCollider2(RECT rcA, RECT rcB)
{
	if (rcA.left < rcB.right  &&
		rcA.top < rcB.bottom &&
		rcA.right > rcB.left &&
		rcA.bottom > rcB.top)
	{
		return true;
	}
	return false;
}

inline int ChangeAlpha(int& alpha, int size)
{
	if (alpha < 0)
	{
		return 0;
	}
	else if (alpha > 255)
	{
		return 255;
	}
	alpha += size;

	return alpha;
}

inline float mRangeNum(float startNum, float smallEnd, float bigEnd, float size,bool &isinc )
{
	if (startNum < smallEnd )
	{
		isinc = true;
		startNum = smallEnd;
	}
	else if (startNum > bigEnd) 
	{
		isinc = false;
		startNum = bigEnd;
	}

	startNum += isinc?  size : -size;
	
	return startNum;
}

inline RectF GPRectFMakeCenter(REAL width, REAL height)
{
	RectF rc = {-width / 2 ,-height / 2, width, height };
	return rc;

}

inline RECT CollisionAreaResizing(RECT &rcDest, int width, int height) 
{
	RECT rc = { rcDest.left + width / 2,
				rcDest.top + height / 2,
				rcDest.right - width / 2,
				rcDest.bottom - height / 2 };
	return rc;
}
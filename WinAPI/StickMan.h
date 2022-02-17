#pragma once

enum MANSTATE
{
	IDLE,
	L_MOVE,
	R_MOVE
};

class StickMan
{
private:
	MANSTATE _manState;
	int centerX;
	int centerY;
	int height;
	int width;
	int left;
	int top;
	int right;
	int bottom;

public:
	void IdleMan(HDC hdc, RECT* rect);
	void LeftMoveMan(HDC hdc, RECT* rect);
	void RightMoveMan(HDC hdc, RECT* rect);

	int getState() { return _manState; }
	void setState(MANSTATE state) { _manState = state; }
};


#include "Stdafx.h"
#include "StickMan.h"


void StickMan::IdleMan(HDC hdc, RECT * rect)
{
	centerX = (rect->left + rect->right) *0.5;
	centerY = (rect->top + rect->bottom) *0.5;
	height = rect->bottom - rect->top;
	width = rect->right - rect->left;
	left = rect->left;
	top = rect->top;
	right = rect->right;
	bottom = rect->bottom;
	//个烹
	LineMake(hdc, centerX, top, centerX, top + height * 0.5);
	//促府
	LineMake(hdc, centerX, top + height * 0.5, left, bottom);
	LineMake(hdc, centerX, top + height * 0.5, right, bottom);
	//迫
	LineMake(hdc, centerX, top + width * 0.7, left, centerY);
	LineMake(hdc, centerX, top + width * 0.7, right, centerY);
	//赣府
	EllipseMakeCenter(hdc, centerX, top + width * 0.3, width * 0.7, width * 0.7);
	//传
	LineMake(hdc, centerX + width * 0.1, top + width * 0.3, centerX + width * 0.3, top + width * 0.3);
	LineMake(hdc, centerX - width * 0.1, top + width * 0.3, centerX - width * 0.3, top + width * 0.3);
}

void StickMan::LeftMoveMan(HDC hdc, RECT* rect)
{
	centerX = (rect->left + rect->right) *0.5;
	centerY = (rect->top + rect->bottom) *0.5;
	height = rect->bottom - rect->top;
	width = rect->right - rect->left;
	left = rect->left;
	top = rect->top;
	right = rect->right;
	bottom = rect->bottom;
	//个烹
	LineMake(hdc, centerX, top, centerX, top + height * 0.5);
	//促府
	LineMake(hdc, centerX,
				top + height * 0.5,
				left+width*0.1,
				centerY+width*0.1);
	LineMake(hdc, left + width * 0.1,
				centerY + width * 0.1,
				left + width * 0.3,
				bottom-width*0.5);
	LineMake(hdc, centerX, top + height * 0.5, right, bottom);
	//迫
	LineMake(hdc, centerX, top + width * 0.7, left + width * 0.1, centerY);
	LineMake(hdc, centerX, top + width * 0.7, right, centerY);
	/*LineMake(hdc, centerX, top + width * 0.7, right, centerY - width*0.8);*/
	//赣府
	EllipseMakeCenter(hdc, centerX, top + width * 0.3, width * 0.7, width * 0.7);
	//传
	/*LineMake(hdc, centerX + width * 0.1, top + width * 0.3, centerX + width * 0.3, top + width * 0.3)*/
	LineMake(hdc, centerX - width * 0.1, top + width * 0.3, centerX - width * 0.3, top + width * 0.3);
}

void StickMan::RightMoveMan(HDC hdc, RECT* rect)
{
	centerX = (rect->left + rect->right) *0.5;
	centerY = (rect->top + rect->bottom) *0.5;
	height = rect->bottom - rect->top;
	width = rect->right - rect->left;
	left = rect->left;
	top = rect->top;
	right = rect->right;
	bottom = rect->bottom;
	//个烹
	LineMake(hdc, centerX, top, centerX, top + height * 0.5);
	//促府
	LineMake(hdc, centerX,
		top + height * 0.5,
		right - width * 0.1,
		centerY + width * 0.1);
	LineMake(hdc, right - width * 0.1,
		centerY + width * 0.1,
		right - width * 0.3,
		bottom - width * 0.5);
	LineMake(hdc, centerX, top + height * 0.5, left, bottom);
	//迫
	LineMake(hdc, centerX, top + width * 0.7, right - width * 0.1, centerY);
	LineMake(hdc, centerX, top + width * 0.7, left, centerY);
	/*LineMake(hdc, centerX, top + width * 0.7, right, centerY - width*0.8);*/
	//赣府
	EllipseMakeCenter(hdc, centerX, top + width * 0.3, width * 0.7, width * 0.7);
	//传
	LineMake(hdc, centerX + width * 0.1, top + width * 0.3, centerX + width * 0.3, top + width * 0.3);
	/*LineMake(hdc, centerX - width * 0.1, top + width * 0.3, centerX - width * 0.3, top + width * 0.3);*/

}

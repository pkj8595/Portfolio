#pragma once
#include "SingletonBase.h"

class FontManager:public SingletonBase<FontManager>
{

public:

	void drawText(HDC hdc, int destX, int destY, char* fileName,char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName,int fontSize,int fontWidth,char* printString, int length,COLORREF color);

	void drawText(HDC hdc, RECT rangeRect, char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color);

	//LPCWSTR(W) - wide char ->unicode
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR printString, int length, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR* printString, int length, COLORREF color);

	FontManager() {}
	~FontManager() {}
};


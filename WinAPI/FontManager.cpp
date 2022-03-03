#include "Stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
}

void FontManager::drawText(HDC hdc, int destX, int destY, char *fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	//TextOut(hdc, destX, destY, printString, length);
	DrawText(hdc, printString, -1, &RectMake(destX, destY, 0, 0), DT_NOCLIP| DT_LEFT);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawTextRectCenter(HDC hdc, RECT rangeRect, char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	DrawText(hdc, printString, -1, &rangeRect, DT_NOCLIP | DT_CENTER);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, RECT rangeRect, char* fontName, int fontSize, int fontWidth, char* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	DrawText(hdc, printString, -1, &rangeRect, DT_WORDBREAK | DT_LEFT);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char *fontName, int fontSize, int fontWidth, LPCWSTR printString, int length, COLORREF color)
{

	
	SetBkMode(hdc, TRANSPARENT);
	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOutW(hdc, destX, destY, printString, length);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);

}

void FontManager::drawText(HDC hdc, int destX, int destY, char *fontName, int fontSize, int fontWidth, LPCWSTR *printStringArr, int length, COLORREF color)
{
	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
}

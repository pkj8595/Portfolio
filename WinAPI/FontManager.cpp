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
	//TextOut(hdc, destX, destY, printString, length);
	DrawText(hdc, printString, -1, &rangeRect, DT_WORDBREAK | DT_LEFT);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char *fontName, int fontSize, int fontWidth, LPCWSTR printString, int length, COLORREF color)
{

	/*
	font = CreateFont
	(
		문자 크기 , 문자폭,문자 전체 기울기, 문자방향,문자굵기,기울기(bool),밑줄(bool),취소선,문자셋팅, 출력정확도,클리핑 정확도,출력의 질(여기서 최적화 기대 x 그냥 최대값으로 넣기),자간,폰트
	);
	*/
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

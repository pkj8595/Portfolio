#include "Stdafx.h"
#include "HPprogressBar.h"


HPprogressBar::HPprogressBar(int maxHp)
{
	_nMaxHp = static_cast<float>(maxHp);
	_nHp = 0;
	temp=0;
}

void HPprogressBar::RenderHpbar(HDC hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	Rectangle(hdc, _rectMaxHp.left, _rectMaxHp.top, _rectMaxHp.right, _rectMaxHp.bottom);
	FillRect(hdc, &_rectMaxHp, brush);
	DeleteObject(brush);

	HBRUSH brush1 = CreateSolidBrush(RGB(0, 0, 255));
	Rectangle(hdc, _rectHp.left, _rectHp.top, _rectHp.right, _rectHp.bottom);
	FillRect(hdc, &_rectHp, brush1); 
	DeleteObject(brush1);

	/*char str[120];
	wsprintf(str, "_hp  %f,  maxhp  %f, right  %d,  left %d,  temp  %f", _nHp,_nMaxHp,_rectMaxHp.right, _rectMaxHp.left,temp);
	TextOut(hdc, 0, 0, str, strlen(str));*/

}

void HPprogressBar::UpdateHpBar(RECT * target, int nHp)
{
	_nHp = static_cast<float>(nHp);
	temp = ((_rectMaxHp.right - _rectMaxHp.left) * (_nHp / _nMaxHp));

	_rectMaxHp = RECT{ target->left,
						target->top- 20,
						target->right,
						target->top- 10 };
	_rectHp = RECT{ _rectMaxHp.left,
					_rectMaxHp.top,
					_rectMaxHp.left+ static_cast<int>(temp),
					_rectMaxHp.bottom };
}

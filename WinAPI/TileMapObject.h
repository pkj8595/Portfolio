#pragma once
#include "GameNode.h"

class TileMapObject 
{
private:
	string _imgStr;
	RECT _lprc;
	POINT _pt;
	int _index;
	bool _isClicked;

public:
	HRESULT init(string filename, RECT rc, int index);
	void release(void);
	void update(POINT pt);
	void render(HDC hdc);

	void ImgRender(const HDC &hdc);

	void setImgStr(string str) { _imgStr = str; }
	void setPoint(POINT pt) { _pt = pt; }
	void setIsClicked(bool isClicked) { _isClicked = isClicked; }

	RECT getLPRc() { return _lprc; }
	POINT getPoint() { return _pt; }
	string getImgStr() { return _imgStr; }
	int getIndex() { return _index; }
	bool getisClicked() { return _isClicked; }

};


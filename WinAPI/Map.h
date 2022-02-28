#pragma once
#include "GameNode.h"

class Player;

class Map : public GameNode
{
public:
	enum class MAPTYPE
	{
		DEFAULT, START, TREASURE, REPAIR, SHOP, BOSS
	};
protected:
	my::Image* _minimapImage;
	my::Image* _image;
	my::Image* _upWall;
	my::Image* _downWall;
	my::Image* _leftWall;
	my::Image* _rightWall;
	my::Image* _pixelCollisionImage;

	POINT _location;
	MAPTYPE _type;

	//Ä³¸¯ÅÍ È°µ¿¹Ý°æ
	RECT _mapRC;

	//¹Ù±ù ¸Ê
	RECT _outsideRcWidth;
	RECT _outsideRcLength;

	bool _show;
	bool _clear;
	bool _connectedMap[4]; //Left, Up, Right, Down

public:
	virtual HRESULT init(POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void showMinimapIcon(int x, int y);
	MAPTYPE getType() { return _type; }
	POINT getLocation() { return _location; }

	bool isShow() { return _show; }
	void setShow(bool show) { _show = show; }
	bool isClear() { return _clear; }
	void setClear(bool clear) { _clear = clear; }

	void setConnectedMap(int arrayNum, bool connected)
	{
		_connectedMap[arrayNum] = connected;
	}

	my::Image* getPixelCollisionImage() { return _pixelCollisionImage; }
	MAPTYPE getMapType() { return _type; }
	bool isConnected(int map) { return _connectedMap[map]; }

	RECT getMapRC() { return _mapRC; }
	void printOutsideRC();

	Map() : _mapRC({ 0,0,WINSIZE_X,WINSIZE_Y }) {}
};


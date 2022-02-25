#pragma once
#include "Map.h"

class DefaultMap : public Map
{
private:
	int _rndMapNum;
	int _leftWallImageFixX;
	int _leftWallImageFixY;
	int _rightWallImageFixX;
	int _rightWallImageFixY;

	bool _pixel;
public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);

	void createRndMapImage();
	
};


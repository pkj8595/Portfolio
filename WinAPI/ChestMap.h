#pragma once
#include "Map.h"

class ChestMap : public Map
{
private:
	my::Image* _chestImage;

	bool _open;
	int _frameY;

	RECT _chestRC;
public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);


};


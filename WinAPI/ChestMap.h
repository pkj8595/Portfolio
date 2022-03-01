#pragma once
#include "Map.h"

class ChestMap : public Map
{
private:
	my::Image* _chestImage;

	bool _open;
	int _frameY;
	RECT _chestRC;

	EventObject* _chestEventObj;
	RECT _chestEventRc;

public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);

	void openChest(void);

};


#pragma once
#include "GameNode.h"
#include "TileMapObject.h"

#define TILE_MAP_MAX		100
#define TILE_MAP_RECT_SIZE	150



class Tilemap : public GameNode
{
private:
	vector<TileMapObject> _vMap;
	vector<TileMapObject>::iterator _viMap;

	bool _isClicked;
	bool _isActive;
	int _tileMapSize;
	int _index;

public:
	HRESULT init(int tileMapSize);
	void release(void);
	void update(void);
	void render(void);

	Tilemap();
	~Tilemap() {}
};


#pragma once
#include "GameNode.h"
#include "Map.h"
#include "StartMap.h"
#include "DefaultMap.h"
#include "BossMap.h"
#include "ChestMap.h"
#include "ShopMap.h"
#include "RepairMap.h"
#include "ItemSpawner.h"

class MapManager : public GameNode
{
private:
	POINT _startPosition;
	int _mapAmount;
	struct tempMapData
	{
		POINT location;
		Map::MAPTYPE type;
	};
	vector<Map*> _vMap;
	vector<Map*>::iterator _viMap;

	vector<tempMapData> _vTempMap;

	Map* _currentMap;

	bool _tempMinimapToggle;
	unsigned short _minimapAlpha;
	bool _isFadeInMinimap;

	ItemSpawner* _itemSpawner;

public:
	HRESULT init(int mapAmount, int stage);
	void release(void);
	void update(void);
	void render(void);

	void createMap(POINT position);
	void createRndMap(POINT position);
	void createSpecialMap(POINT startPosition);
	bool isOneEntrance(tempMapData mapdata);
	bool isTwoEntrance(tempMapData mapdata);
	void setMapData();
	void setConnectedMap();

	void changeMap(int pos);
	void printTempMinimap();
	bool isNearCurrentMap(Map* currentmap, Map* targetMap);

	Map* getCurrentMap() { return _currentMap; }
	my::Image* getCurrentMapPixel()
	{
		return _currentMap->getPixelCollisionImage();
	}

	bool isMinimapToggle()	{ return _tempMinimapToggle; }

public:
	//debug 
	void debugAroundMap();
	void printMap(Map::MAPTYPE type);
};


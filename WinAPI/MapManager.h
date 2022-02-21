#pragma once
#include "GameNode.h"
#include "Map.h"
#include "StartMap.h"
#include "DefaultMap.h"
#include "BossMap.h"
#include "ChestMap.h"

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

public:
	HRESULT init(int mapAmount);
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

	void changeMap(void);
	void printTempMinimap();
	bool isNearCurrentMap(Map* currentmap, Map* targetMap);
};


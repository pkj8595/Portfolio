#include "Stdafx.h"
#include "MapManager.h"

HRESULT MapManager::init(int mapAmount, int stage)
{
	int i = 0;
	IMAGEMANAGER->addImage("Minimap_Off", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cell_off.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Minimap_Current", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cell_shop.bmp", 30, 30, true, RGB(255, 0, 255));

	_startPosition = { 5, 5 };
	_mapAmount = mapAmount;
	ZeroMemory(&_vTempMap, sizeof(_vTempMap));
	createMap(_startPosition);
	setMapData();
	setConnectedMap();
	
	_tempMinimapToggle = false;

	_minimapAlpha = 0;
	_isFadeInMinimap = true;

	return S_OK;
}

void MapManager::release(void)
{
}

void MapManager::update(void)
{
	_currentMap->update();
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_tempMinimapToggle = !_tempMinimapToggle;
	}
	(_isFadeInMinimap) ? _minimapAlpha += 10 : _minimapAlpha -= 10;
	if (_minimapAlpha >= 180) _isFadeInMinimap = false;
	else if (_minimapAlpha <= 0) _isFadeInMinimap = true;

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_currentMap->setClear(true);
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		for (Map* m : _vMap)
		{
			if (m->getType() == Map::MAPTYPE::BOSS)
			{
				_currentMap = m;
				_currentMap->setShow(true);
			}
		}
	}


}

void MapManager::render(void)
{
	_currentMap->render();

}

void MapManager::createMap(POINT position)
{
	while (_mapAmount > 0) createRndMap(position);
	createSpecialMap(_startPosition);
}

void MapManager::createRndMap(POINT position)
{
	if (_mapAmount <= 0) return;
	
	bool tempCheckOverlap = false;
	for (tempMapData iter : _vTempMap)
	{
		if (iter.location.x == position.x && iter.location.y == position.y) tempCheckOverlap = true;
	}
	
	if (!tempCheckOverlap)
	{
		int aroundCount = 0;
		for (tempMapData iter : _vTempMap)
		{
			if (iter.location.x == position.x - 1 && iter.location.y == position.y) aroundCount++;
			else if (iter.location.x == position.x + 1 && iter.location.y == position.y) aroundCount++;
			else if (iter.location.x == position.x && iter.location.y == position.y - 1) aroundCount++;
			else if (iter.location.x == position.x && iter.location.y == position.y + 1) aroundCount++;
		}
		if (aroundCount >= 2) return;
		else
		{

			tempMapData temp;
			temp.location = position;
			temp.type = Map::MAPTYPE::DEFAULT;
			_vTempMap.push_back(temp);
			_mapAmount--;
		}
	}

	int tempRnd = RND->getInt(18);
	switch (tempRnd)
	{
	case 0:
	{
		createRndMap({ position.x, position.y - 1 });
	} break;
	case 1:
	{
		createRndMap({ position.x, position.y + 1 });
	} break;
	case 2:
	{
		createRndMap({ position.x - 1, position.y });
	} break;
	case 3:
	{
		createRndMap({ position.x + 1, position.y });
	} break;
	case 4:
	{
		createRndMap({ position.x , position.y - 1 });
		createRndMap({ position.x , position.y + 1 });
	} break;
	case 5:
	{
		createRndMap({ position.x, position.y - 1 });
		createRndMap({ position.x - 1, position.y });
	} break;
	case 6:
	{
		createRndMap({ position.x, position.y - 1 });
		createRndMap({ position.x + 1, position.y });
	} break;
	case 7:
	{
		createRndMap({ position.x, position.y + 1 });
		createRndMap({ position.x - 1, position.y });
	} break;
	case 8:
	{
		createRndMap({ position.x, position.y + 1 });
		createRndMap({ position.x - 1, position.y });
	} break;
	case 9:
	{
		createRndMap({ position.x - 1, position.y });
		createRndMap({ position.x + 1, position.y });
	} break;
	case 10:
	{
		createRndMap({ position.x , position.y - 1 });
		createRndMap({ position.x , position.y + 1});
		createRndMap({ position.x + 1, position.y });
	} break;
	case 11:
	{
		createRndMap({ position.x, position.y + 1 });
		createRndMap({ position.x - 1, position.y });
		createRndMap({ position.x, position.y - 1 });
	} break;
	case 12:
	{
		createRndMap({ position.x , position.y + 1 });
		createRndMap({ position.x + 1, position.y });
		createRndMap({ position.x - 1, position.y });
	} break;
	case 13:
	{
		createRndMap({ position.x + 1, position.y });
		createRndMap({ position.x - 1, position.y });
		createRndMap({ position.x, position.y - 1 });
	} break;
	case 14:
	{
		createRndMap({ position.x, position.y - 1 });
		createRndMap({ position.x - 1, position.y });
		createRndMap({ position.x, position.y + 1 });
		createRndMap({ position.x + 1, position.y });
	} break;
	default:break;
	}
}

void MapManager::createSpecialMap(POINT startPosition) 
{
	//find One or Two Entrance Map
	vector<tempMapData> tempData;
	for (int i = 0; i < _vTempMap.size(); i++)
	{
		if (_vTempMap[i].location.x == startPosition.x && _vTempMap[i].location.y == startPosition.y)
		{
			_vTempMap[i].type = Map::MAPTYPE::START;
		}

		else if (isOneEntrance(_vTempMap[i]))
		{
			tempData.push_back(_vTempMap[i]);
		}
	}
	if (tempData.size() <= 1)
	{
		for (int i = 0; i < _vTempMap.size(); i++)
		{

			if (isTwoEntrance(_vTempMap[i]) && _vTempMap[i].type != Map::MAPTYPE::START)
			{
				tempData.push_back(_vTempMap[i]);
			}
		}
	}

	//set selecMap to Boss, TreasureMap
	int tempIndexA = RND->getInt(tempData.size());
	int tempIndexB = RND->getInt(tempData.size());
	while (tempIndexA == tempIndexB)
	{
		tempIndexB = RND->getInt(tempData.size());
	}
	tempMapData tempMapA = tempData[tempIndexA];
	tempMapData tempMapB = tempData[tempIndexB];

	for (int i = 0; i < _vTempMap.size(); i++)
	{

		if (tempMapA.location.x == _vTempMap[i].location.x && tempMapA.location.y == _vTempMap[i].location.y)
		{
			_vTempMap[i].type = Map::MAPTYPE::BOSS;
		}
		if (tempMapB.location.x == _vTempMap[i].location.x && tempMapB.location.y == _vTempMap[i].location.y)
		{
			_vTempMap[i].type = Map::MAPTYPE::TREASURE;
		}
	}

	//create Shop, RepairMap
	int tempIndexC = RND->getInt(_vTempMap.size());
	while (_vTempMap[tempIndexC].type != Map::MAPTYPE::DEFAULT)
	{
		tempIndexC = RND->getInt(_vTempMap.size());
	}
	tempMapData tempMapC = _vTempMap[tempIndexC];
	for (int i = 0; i < _vTempMap.size(); i++)
	{
		if (tempMapC.location.x == _vTempMap[i].location.x && tempMapC.location.y == _vTempMap[i].location.y)
		{
			_vTempMap[i].type = Map::MAPTYPE::SHOP;
		}
	}

	int tempIndexD = RND->getInt(_vTempMap.size());
	while (_vTempMap[tempIndexD].type != Map::MAPTYPE::DEFAULT)
	{
		tempIndexD = RND->getInt(_vTempMap.size());
	}
	tempMapData tempMapD = _vTempMap[tempIndexD];
	for (int i = 0; i < _vTempMap.size(); i++)
	{
		if (tempMapD.location.x == _vTempMap[i].location.x && tempMapD.location.y == _vTempMap[i].location.y)
		{
			_vTempMap[i].type = Map::MAPTYPE::REPAIR;
		}
	}
}

bool MapManager::isOneEntrance(tempMapData mapdata)
{
	int aroundCount = 0;
	for (tempMapData iter : _vTempMap)
	{
		if (iter.location.x == mapdata.location.x - 1 && iter.location.y == mapdata.location.y) aroundCount++;
		else if (iter.location.x == mapdata.location.x + 1 && iter.location.y == mapdata.location.y) aroundCount++;
		else if (iter.location.x == mapdata.location.x && iter.location.y == mapdata.location.y - 1) aroundCount++;
		else if (iter.location.x == mapdata.location.x && iter.location.y == mapdata.location.y + 1) aroundCount++;
	}

	if (aroundCount == 1) return true;
	else return false;
}

bool MapManager::isTwoEntrance(tempMapData mapdata)
{
	int aroundCount = 0;
	for (tempMapData iter : _vTempMap)
	{
		if (iter.location.x == mapdata.location.x - 1 && iter.location.y == mapdata.location.y) aroundCount++;
		else if (iter.location.x == mapdata.location.x + 1 && iter.location.y == mapdata.location.y) aroundCount++;
		else if (iter.location.x == mapdata.location.x && iter.location.y == mapdata.location.y - 1) aroundCount++;
		else if (iter.location.x == mapdata.location.x && iter.location.y == mapdata.location.y + 1) aroundCount++;
	}

	if (aroundCount == 2) return true;
	else return false;
}

void MapManager::setMapData()
{
	for (tempMapData iter : _vTempMap)
	{
		switch (iter.type)
		{
		case Map::MAPTYPE::START:
		{
			Map* map;
			map = new StartMap;
			map->init(iter.location);
			_vMap.push_back(map);
			_currentMap = map;
		} break;
		case Map::MAPTYPE::DEFAULT:
		{
			Map* map;
			map = new DefaultMap;
			map->init(iter.location);
			_vMap.push_back(map);
		} break;
		case Map::MAPTYPE::BOSS:
		{
			Map* map;
			map = new BossMap;
			map->init(iter.location);
			_vMap.push_back(map);
		} break;
		case Map::MAPTYPE::TREASURE:
		{
			Map* map;
			map = new ChestMap;
			map->init(iter.location);
			_vMap.push_back(map);
		} break;
		case Map::MAPTYPE::SHOP:
		{
			Map* map;
			map = new ShopMap;
			map->init(iter.location);
			_vMap.push_back(map);
		} break;
		case Map::MAPTYPE::REPAIR:
		{
			Map* map;
			map = new RepairMap;
			map->init(iter.location);
			_vMap.push_back(map);
		} break;
		default: break;

		}
	}
}

void MapManager::setConnectedMap()
{
	_viMap = _vMap.begin();
	for (; _viMap != _vMap.end(); ++_viMap)
	{
		for (int i = 0; i < _vMap.size(); i++)
		{
			if ((*_viMap)->getLocation().x - 1 == _vMap[i]->getLocation().x && (*_viMap)->getLocation().y == _vMap[i]->getLocation().y)
			{
				(*_viMap)->setConnectedMap(0, true);
			}
			if ((*_viMap)->getLocation().x == _vMap[i]->getLocation().x && (*_viMap)->getLocation().y - 1 == _vMap[i]->getLocation().y)
			{
				(*_viMap)->setConnectedMap(1, true);
			}
			if ((*_viMap)->getLocation().x + 1 == _vMap[i]->getLocation().x && (*_viMap)->getLocation().y == _vMap[i]->getLocation().y)
			{
				(*_viMap)->setConnectedMap(2, true);
			}
			if ((*_viMap)->getLocation().x == _vMap[i]->getLocation().x && (*_viMap)->getLocation().y + 1 == _vMap[i]->getLocation().y)
			{
				(*_viMap)->setConnectedMap(3, true);
			}
		}
	}
}

//0, 1, 2, 3 : LEFT, RIGHT, UP, DOWN
void MapManager::changeMap(int pos) 
{
	if (pos == 0 && _currentMap->isClear())
	{
		for (Map* m : _vMap)
		{

			if (m->getLocation().x + 1 == _currentMap->getLocation().x && m->getLocation().y == _currentMap->getLocation().y)
			{
				_currentMap = m;
				_currentMap->setShow(true);
				break;
			}
		}
	}
	if (pos == 1 && _currentMap->isClear())
	{
		for (Map* m : _vMap)
		{
			if (m->getLocation().x - 1 == _currentMap->getLocation().x && m->getLocation().y == _currentMap->getLocation().y)
			{
				_currentMap = m;
				_currentMap->setShow(true);
				break;
			}
		}
	}
	if (pos == 2 && _currentMap->isClear())
	{
		for (Map* m : _vMap)
		{
			if (m->getLocation().x == _currentMap->getLocation().x && m->getLocation().y + 1 == _currentMap->getLocation().y)
			{
				_currentMap = m;
				_currentMap->setShow(true);
				break;
			}
		}
	}
	if (pos == 3 && _currentMap->isClear())
	{
		for (Map* m : _vMap)
		{
			if (m->getLocation().x == _currentMap->getLocation().x && m->getLocation().y - 1 == _currentMap->getLocation().y)
			{
				_currentMap = m;
				_currentMap->setShow(true);
				break;
			}
		}
	}
}

void MapManager::printTempMinimap()
{
	if (_tempMinimapToggle)
	{
		_viMap = _vMap.begin();
		for (; _viMap != _vMap.end(); ++_viMap)
		{
			if ((*_viMap)->isShow())
			{
				(*_viMap)->showMinimapIcon(350, 300);
			}
			else
			{
				for (int i = 0; i < _vMap.size(); i++)
				{
					if (isNearCurrentMap(_vMap[i], *_viMap))
					{
						IMAGEMANAGER->findImage("Minimap_Off")->alphaRender(getMemDC(),
							350 + (*_viMap)->getLocation().x * IMAGEMANAGER->findImage("Minimap_Off")->getWidth(),
							300 + (*_viMap)->getLocation().y * IMAGEMANAGER->findImage("Minimap_Off")->getHeight(), 180);
					}
				}
			}
		}
	}
	IMAGEMANAGER->findImage("Minimap_Current")->alphaRender(getMemDC(),
		350 + _currentMap->getLocation().x * IMAGEMANAGER->findImage("Minimap_Current")->getWidth(),
		300 + _currentMap->getLocation().y * IMAGEMANAGER->findImage("Minimap_Current")->getHeight(), _minimapAlpha);
}

bool MapManager::isNearCurrentMap(Map * currentmap, Map * targetMap)
{
	if (!currentmap->isShow()) return false;

	if (targetMap->getLocation().x == currentmap->getLocation().x - 1 &&
		targetMap->getLocation().y == currentmap->getLocation().y) return true;
	else if (targetMap->getLocation().x == currentmap->getLocation().x + 1 &&
		targetMap->getLocation().y == currentmap->getLocation().y) return true;
	else if (targetMap->getLocation().x == currentmap->getLocation().x &&
		targetMap->getLocation().y == currentmap->getLocation().y - 1) return true;
	else if (targetMap->getLocation().x == currentmap->getLocation().x  &&
		targetMap->getLocation().y == currentmap->getLocation().y + 1) return true;
	else return false;
}

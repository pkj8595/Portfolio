#pragma once
#include "GameNode.h"
#include "IRectObserved.h"

#define ITEM_OBJ_SIZE		32
#define MOVE_OFFSET_TIME	0.2f	
#define CHANGE_DIRECTION	1.0F

class Map;
class ItemManager;
class ItemObject :public GameNode, public IRectObserved
{
private:
	ItemManager* _itemManager;
	ObservedType _typeKey;
	RECT _rc;
	Map* _map;

	float _x, _y;
	int _itemIndex;
	bool _isActive;
	bool _increaseY;
	bool _isCollider;
	float _worldTime;
	float _responseTime;
	float _moveOffsetTime;

public:
	HRESULT init(void);
	HRESULT init(int x, int y, bool isCollider);
	void release(void);
	void update(void);
	void render(void);

	int getItemIndex(void) { return _itemIndex; }
	bool getIsActive(void) { return _isActive; }
	void setIsActive(bool isActive) { _isActive = isActive; }
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);
	
	Map* getMap() { return _map; }
	void setMap(Map* map) { _map = map; }
};

class ItemSpawner :public SingletonBase<ItemSpawner>
{
private:
	vector<ItemObject*> _vItemObj;
	vector<ItemObject*>::iterator _viItemObj;

	Map** _currentMap;
	
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	int createItem(int x, int y, bool isCollider);
	ItemObject* createItemMapInit(int x, int y, bool isCollider, Map* map);
	void removeItem(ItemObject* itemObject);

	void clearItem(void);
	void setCurrentMap(Map** cmap);

	ItemSpawner();
	~ItemSpawner();
};

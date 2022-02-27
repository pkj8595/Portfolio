#pragma once
#include "GameNode.h"
#include "ItemManager.h"
#include "IRectObserved.h"

#define ITEM_OBJ_SIZE		64
#define MOVE_OFFSET_TIME	0.2f	
#define CHANGE_DIRECTION	1.0F

class ItemObject :public GameNode, public IRectObserved
{
private:
	ItemManager* _itemManager;
	ObservedType _typeKey;
	RECT _rc;
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
	bool getIsActive(void) { return _isActive; }
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

};

class ItemSpawner :public GameNode
{
private:
	vector<ItemObject*> _vItemObj;
	vector<ItemObject*>::iterator _viItemObj;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void createItem(int x, int y, bool isCollider);
	void clearItem(void);

};

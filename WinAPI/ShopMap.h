#pragma once
#include "Map.h"
#include "EventObject.h"

#define ITEM_SIZE	5

class ItemManager;
class ItemSpawner;
class ItemObject;
class ShopMap : public Map
{
private:
	my::Image* _shopBar;
	my::Image* _shopNPC;
	int _x, _y;


	ItemManager* _itemManager;
	ItemSpawner* _itemSpawner;


	typedef struct tagEventObj
	{
		ItemObject* itemObj;
		EventObject* eventObj;
		tagEventObj()
		{
			itemObj = nullptr;
			eventObj = nullptr;
		}
	}ShopEventObj;

	ShopEventObj _eventObj[ITEM_SIZE];
	RECT _rcEvent[ITEM_SIZE];

	

public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
};


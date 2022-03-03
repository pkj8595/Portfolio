#pragma once
#include "Map.h"


#define ITEM_SIZE	5

class ShopMap : public Map
{
private:
	ItemManager* _itemManager;
	ItemSpawner* _itemSpawner;
	my::Image* _shopBar;
	my::Image* _shopNPC;

	RECT tempRc;

	
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
	vector<ShopEventObj> _vObj;
	vector<ShopEventObj>::iterator _viObj;

	RECT _rcEvent[ITEM_SIZE];

	

public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
};


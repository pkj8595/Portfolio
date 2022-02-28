#pragma once
#include "Map.h"

#define ITEM_SIZE	5

class ItemManager;
class ItemSpawner;
class ShopMap : public Map
{
private:
	my::Image* _shopBar;
	my::Image* _shopNPC;
	RECT _shopCollider;
	int _x, _y;

	int _itemIndex[ITEM_SIZE];

	ItemManager* _itemManager;
	ItemSpawner* _itemSpawner;

public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
};


#pragma once
#include "Map.h"
#include "ItemManager.h"

class ShopMap : public Map
{
private:
	my::Image* _shopBar;
	my::Image* _shopNPC;
	RECT _shopCollider;
	int _x, _y;

	ItemManager* _itemManager;

public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
};


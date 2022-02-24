#pragma once
#include "GameNode.h"
#include "ItemManager.h"
#include "Inventory.h"
class ShopScene : public GameNode
{
private:
	ItemManager* _itemManager;
	Inventory* _inven;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};


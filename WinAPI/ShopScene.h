#pragma once
#include "GameNode.h"
#include "ItemManager.h"
class ShopScene : public GameNode
{
private:
	ItemManager* _itemManager;

public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};


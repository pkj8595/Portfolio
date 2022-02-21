#pragma once
#include "ItemClass.h"
#include "GameNode.h"

class ItemManager : public GameNode
{
private:
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;
	int _index;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void setItemList();

	ItemManager() {}
	~ItemManager() {}
};


#pragma once
#include "ItemClass.h"
#include "GameNode.h"

class ItemManager : public GameNode
{
private:
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;
	my::Image* _itemImg;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	my::Image* getImage(void) { return _itemImg; }
	Item* getItem(int imgIndex);
	void itemImgRender(int index, int x, int y);
	//void ItemWindowRender(void);


	ItemManager() {}
	~ItemManager() {}
};


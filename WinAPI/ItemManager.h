#pragma once
#include "ItemClass.h"
#include "GameNode.h"

#define IMAGE_SIZE		32

class ItemManager : public GameNode
{
private:
	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;
	my::Image* _itemImg;
	my::Image* _bigItemImg;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	my::Image* getImage(void) { return _itemImg; }
	Item* getItem(int imgIndex);
	Item* getItemIndex(int index);
	void getItemImgRender(int imgIndex, int x, int y);
	void getBigItemImgRender(int imgIndex, int x, int y);
	//void ItemWindowRender(void);


	ItemManager() {}
	~ItemManager() {}
};


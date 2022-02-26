#pragma once
#include "ItemClass.h"
#include "GameNode.h"

#define IMAGE_SIZE		32

class ItemManager : public SingletonBase<ItemManager>
{
private:
	my::Image* _itemImg;
	my::Image* _bigItemImg;

	vector<Item*> _vItem;
	vector<Item*>::iterator _viItem;

	vector<EnchantItem*> _vEnchantItem;
	vector<EnchantItem*>::iterator _viEnchantItem;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	my::Image* getImage(void) { return _itemImg; }
	Item* getItem(int imgIndex);
	Item* getItemIndex(int index);
	void getItemImgRender(HDC hdc,int imgIndex, int x, int y);
	void getBigItemImgRender(HDC hdc,int imgIndex, int x, int y);
	void getItemIndexRender(HDC hdc, int index, int x, int y);
	void getBigItemIndexRender(HDC hdc, int index, int x, int y);

	EnchantItem* getEnchantItem();
	int getItemSize() { return _vItem.size(); }


	ItemManager();
	~ItemManager();
};


#pragma once
#include "GameNode.h"


struct afterImageSet
{
	float x;
	float y;
	int frame;
	int alpha;
};
class PlayerAfterImage : public GameNode
{
private:
	my::Image* _image0;
	my::Image* _image1;
	my::Image* _image2;
	my::Image* _image3;
	my::Image* _image4;
	my::Image* _image5;
	vector<afterImageSet> _vAfterImage;
	vector<afterImageSet>::iterator _viAfterImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void createAfterImage(float x, float y, int startX);
};


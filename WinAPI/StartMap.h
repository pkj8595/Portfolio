#pragma once
#include "Map.h"
class StartMap : public Map
{
private:
	my::Image* _floorText;
	int _textAlpha;
	float _showTextTime;
	bool _textFadeIn;
	bool _pixel;
public:
	HRESULT init(POINT location);
	void release(void);
	void update(void);
	void render(void);
	void mapText(void);
};


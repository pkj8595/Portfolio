#pragma once
#include "GameNode.h"
#include "TextSystemManager.h"

class Lobby : public GameNode
{
private:
	TextSystemManager* _tsm;
	
	RECT _p_rc;
	RECT _Bookrc;
	RECT _Boxrc;

	bool collBox;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	virtual void collision(void);

	Lobby() {}
	~Lobby() {}
};


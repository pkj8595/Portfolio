#pragma once
#include "GameNode.h"
#include "TextSystemManager.h"
#include "Player.h"

class Lobby : public GameNode
{
private:
	TextSystemManager* _tsm;
	
	Player* _player;

	RECT rc;
	RECT _p_rc;
	RECT _book_rc;
	RECT _box_rc;
	RECT _closet_rc;
	RECT _mirror_rc;
	RECT _window_rc;
	RECT _door_rc;
	RECT _select_rc;

	bool collBox;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	virtual void Collision(void);
	void LobbyCollision(void);

	Lobby() {}
	~Lobby() {}
};


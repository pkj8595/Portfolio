#pragma once
#include "MainGame.h"


enum PLAYER_STATE_0114
{
	STATE_IDLE = 0,
	STATE_MOVE,
	STATE_ATTACK,
	STATE_M_ATTACK,
	STATE_CICLE,
	STATE_VICTORY
};

class Homework_0114_frameImg : public MainGame
{
private:

	PLAYER_STATE_0114 _state;

	my::Image* _background;
	my::Image* _playerIdle;
	my::Image* _playerMove;
	my::Image* _playerAttack;
	my::Image* _playerMAttack;
	my::Image* _playerCicleAttack;
	my::Image* _playerVictory;

	RECT _rcPlayer;
	bool _isLeft;
	bool _isAnimating;

	int _count;
	int _index;


public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	void PlayFrameAnimation(my::Image * image,  bool isleft, int &index);
	bool PlayOnceAnimation(my::Image * image, bool isleft, int &index, bool &isAnimating);


	virtual void render(HDC hdc);



	Homework_0114_frameImg() {}
	~Homework_0114_frameImg() {}
};


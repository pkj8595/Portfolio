#pragma once
#include "MainGame.h"
#include "HPprogressBar.h"


//슈팅 게임 [Base]

//총알의 최대 갯수
#define BULLET_MAX	10
#define PLAYER_SPEED	3
#define ENEMY_MAX	60 //런 타임에서 지워질 여지가 있는가? 지워질 여지가 있다면 벡터를 쓰면 안된다.

//발사체 관리
struct tagBullet0104
{
	RECT rc;
	bool isfire;
};

//적을 관리할 구조체
struct  tagEnemy
{
	RECT rc;
	int speed;
	bool die;
	int damage;
};

struct tagPlayer
{
	RECT rc;
	int hp;
};

class GameClass_0104 : public Scene_inter
{
private:
	tagBullet0104 _bullet[BULLET_MAX];
	tagEnemy _enemy[ENEMY_MAX];
	tagPlayer _player; // 플레이어가 없다면 총알을 만들줄 필요가 없다.
	HPprogressBar _bar;

	bool isGameOver;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void fire(void);

	bool RectIsCollider(RECT* rec1, RECT* rec2);

	GameClass_0104() {}
	virtual ~GameClass_0104() {}
};






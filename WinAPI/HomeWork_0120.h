#pragma once
#include "GameNode.h"
#include "CPlayer.h"
#include "TempSoundTest.h"

#define NOTE_SPEED	5

class HomeWork_0120 :public GameNode
{
private:
	struct STNote
	{
		RECT rc;
		int color;
		bool isActive;
	};
	struct STScoreRc
	{
		RECT rc;
		bool isActive;
	};
	STNote _note;
	vector<STNote*> _vnote;
	vector<STNote*>::iterator _iter;
	STScoreRc _scoreLine[4];
	int _count;
	int _binaryResult;
	int _binaryNum;
	bool _isPlay;
	
	inline void collisionNote(int noteIndex);

public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);	
	virtual void render(HDC hdc);


	HomeWork_0120() {}
	~HomeWork_0120() {}

};


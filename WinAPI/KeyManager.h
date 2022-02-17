#pragma once
#include "SingletonBase.h"

#define KEY_MAX		256

class KeyManager:public SingletonBase<KeyManager>
{
private:
	//BOOL _keyUp[KEY_MAX];
	//BOOL _keyDown[KEY_MAX];

	bitset<KEY_MAX> _keyUp;
	bitset<KEY_MAX> _keyDown;

public:
	HRESULT init(void);
	//키를 눌렀는지
	bool isOnceKeyDown(int key);
	//한번 누르고 띄었는지
	bool isOnceKeyUp(int key);
	//키가 눌려있는지 
	bool isStayKeyDown(int key);
	//토글 키
	bool isToggleKey(int key);

	//키상태 체크 
	bitset<KEY_MAX>getKeyUp(void) { return _keyUp; }
	bitset<KEY_MAX>getKeyDown(void) { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager() {}
	~KeyManager() {}
};


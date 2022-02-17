#pragma once
#include "SingletonBase.h"

class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//씬추가
	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	//씬교체
	HRESULT changeScene(string sceneName);

	//로딩 스레드 함수
	//LPVOID : void* 형(어떤 타입으로도 변환가능)
	//friend : 는 단방향이다.
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	SceneManager() {}
	~SceneManager() {}
};

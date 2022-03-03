#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

//항상 안전에 기한다.
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

//죽은 친구 콜백을 생략..
DWORD CALLBACK loadingThread(LPVOID prc)
{
	//교체될 씬의 함수 실행
	SceneManager::_readyScene->init();

	//현재 씬을 교체될 씬으로 변경
	SceneManager::_currentScene = SceneManager::_readyScene;

	//로딩 씬 해제
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;

	return 0;
}


HRESULT SceneManager::init(void)
{
	_currentScene = nullptr;
	_loadingScene = nullptr;
	_readyScene = nullptr;

	return S_OK;
}

void SceneManager::release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	//로딩씬 -> 교체 대기중인 씬 -> 현재 씬

	//for (0) or while(0) or do~while(0) 시간 복잡도를 따지려면 적어도 1만개 이상

	for (; miSceneList != _mSceneList.end();) 
	{
		if (miSceneList->second != nullptr) 
		{
			if (miSceneList->second == _currentScene) 
			{
				miSceneList->second->release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mSceneList.clear();

	/*
	//라인수가 짫다고 좋은 코드는 아니다.
	for each(auto scene in _mSceneList) 
	{
		SAFE_DELETE(miSceneList->second);
		miSceneList = _mSceneList.erase(miSceneList);
	}*/
}

void SceneManager::update(void)
{
	//현재 씬이 존재하면 현재 씬만 갱신
	if (_currentScene) _currentScene->update();
}

void SceneManager::render(void)
{
	//현재 씬이 존재하면 현재 씬만 렌더
	if (_currentScene) _currentScene->render();
}

GameNode* SceneManager::addScene(string sceneName, GameNode * scene)
{
	//씬이 없다면 리턴
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

GameNode* SceneManager::addLoadingScene(string loadingSceneName, GameNode * scene)
{
	//씬이 없다면 리턴
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(loadingSceneName, scene));

	return scene;
}

HRESULT SceneManager::changeScene(string sceneName)
{
	//변경하려고 하는 씬을 찾는다.
	mapSceneIter find = _mSceneList.find(sceneName);
	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return S_OK;

	//씬을 초기화하고 불러온다.
	if (SUCCEEDED(find->second->init())) 
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}

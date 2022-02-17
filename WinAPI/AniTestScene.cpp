#include "Stdafx.h"
#include "AniTestScene.h"

HRESULT AniTestScene::init(void)
{
	//_image = IMAGEMANAGER->addImage("코끼리", "Resource/Images/Object/Ell.bmp", 660, 268, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addImage("전장", "Resource/Images/Object/Ell.bmp", 660, 268, true, RGB(255, 0, 255));

	_animationA = new Animation;
	//x:6 y:4 
	//함수 매개변수에 연산이 들어가면
	//이미지에 연산이 들어가면 호출될때마다 연산이 들어간다.
	//리소스에 연산이 들어가는 것을 매우 좋지않음. 상수추천
	_animationA->init(_image->getWidth(), _image->getHeight(),110,67);
	_animationA->setDefPlayFrame(false, true);
	_animationA->setFPS(10);

	return S_OK;
}

void AniTestScene::release(void)
{
	_animationA->release();
	SAFE_DELETE(_animationA);
}

void AniTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('B')) 
	{
		_animationA->AniStart();
	}
	_animationA->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

}

void AniTestScene::render(void)
{
	//_image->
	_image->aniRender(getMemDC(),CENTER_X-50,CENTER_Y,_animationA);
}

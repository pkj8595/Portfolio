#pragma once
//=================
//#Singleton base#
//=================
template <class T>
class SingletonBase 
{
	//디자인 패턴(싱글톤)
	//-프로젝트 전체에서 한개만 존재해야 하는 객체나 클래스, 또는 프로젝트 전체에서 공유하는 클래스에 적용할 수 있는 패턴

protected:
	//싱글톤 인스텐스 선언
	static T* singleton;

	SingletonBase() {};
	~SingletonBase() {};


public:
	//싱글톤 가져오기 
	static T* getSingleton(void);
	//싱글톤 메모리에서 해제
	void releaseSingleton(void);

};

//싱글톤 가져오기
template <typename T>
T* SingletonBase<T>::singleton = 0;

template<typename T>
T* SingletonBase<T>::getSingleton(void) 
{
	//싱글톤이 없으면 새로 생성
	if (!singleton) singleton = new T;
	return singleton;
}

template <typename T>
void SingletonBase<T>::releaseSingleton(void) 
{
	//싱글톤이 있다면 메모리에서 해제 
	if (singleton) 
	{
		delete singleton;
		//포인터로 생성 실패시
}
		singleton = 0;
	}


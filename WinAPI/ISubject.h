#pragma once
#include "IRectObserved.h"



class IRectSubject 
{
public:
	virtual void registerObserved(IRectObserved* observed)=0;
	virtual void removeObserved(IRectObserved* observed)=0;
	virtual void getRectFromObserved()=0;

	IRectSubject() {}
	virtual~IRectSubject() {}
};
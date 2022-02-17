#pragma once

class Scene_inter 
{
public:
	virtual HRESULT init(void) =0;
	virtual void release(void)=0;
	virtual void update(void)=0;	
	virtual void render(HDC hdc)=0;
};

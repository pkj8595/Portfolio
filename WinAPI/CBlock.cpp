#include "Stdafx.h"
#include "CBlock.h"



CBlock::CBlock() :_rc(RectF{ -400,-400,0,0 }), _time(5000), _isActive(false), _size(4), _imgKey(""), _penWidth(3), _drection(POSITION), _speed(20), _timeOffset(3000), _isPen(true), _addAngle(0), _isFlash(false), _activeTime(10000), _isExecuteFlash(false), _angle(0), _isFlashReady(false), _isRandomOffsetTime(true), _isReadyPosition(false), _dir(ST_Dir{ 0,0 })
{
	_outRc = RECT{ -450,-450,WINSIZE_X + 900,WINSIZE_Y + 900 };
}


void CBlock::setResetRc(RectF rc, INT speed, bool ispen, REAL penWidth, int timeoffset, blockDrection drec)
{
	_imgKey = "";
	_rc = rc;
	_speed = speed;
	_isPen = ispen;
	_penWidth = penWidth;
	_timeOffset = timeoffset;
	_drection = drec;

	_time =0;
	_activeTime = 0;
	_whiteTime = 0;
	_isFlash = false;
	_size = 0;
	_addAngle =0;
	_angle =0;
	_isFlashReady = false;
	_isReadyPosition = false;
	_isRandomOffsetTime = true;

	PointF temp;
	switch (_drection)
	{
	case LEFT:
		temp.X = WINSIZE_X + 200;
		temp.Y = (REAL)RND->getFromIntTo(50, WINSIZE_Y - 50);
		this->setPosition(temp);
		break;
	case TOP:
		temp.X = (REAL)RND->getFromIntTo(50, WINSIZE_X - 50);
		temp.Y = WINSIZE_Y + 200;
		this->setPosition(temp);
		break;
	case RIGHT:
		temp.X = -200;
		temp.Y = (REAL)RND->getFromIntTo(50, WINSIZE_Y - 50);
		this->setPosition(temp);
		break;
	case BOTTOM:
		temp.X = (REAL)RND->getFromIntTo(50, WINSIZE_X - 50);
		temp.Y = -200;
		this->setPosition(temp);
		break;
	case POSITION:
		break;
	default:
		break;
	}
	_isActive = true;

	
}

void CBlock::setResetImg(string key, float size, INT speed, int timeoffset, blockDrection drec)
{
	_imgKey = key;
	_speed = speed;
	_size = size;
	_timeOffset = timeoffset;
	_drection = drec;

	_isPen = false;
	_rc = RectF(0,0,0,0);
	_time =0;
	_activeTime =0;
	_whiteTime=0;
	_timeOffset=0;
	_isFlash=false;
	_angle =0;
	_penWidth = 0;
	_isFlashReady = false;
	_isReadyPosition = false;
	_isRandomOffsetTime = true;

	PointF temp;
	switch (_drection)
	{
	case LEFT:
		temp.X = WINSIZE_X + 200;
		temp.Y = (REAL)RND->getFromIntTo(50, WINSIZE_Y - 50);
		this->setPosition(temp);
		break;
	case TOP:
		temp.X = (REAL)RND->getFromIntTo(50, WINSIZE_X - 50);
		temp.Y = WINSIZE_Y + 200;
		this->setPosition(temp);
		break;
	case RIGHT:
		temp.X = -200;
		temp.Y = (REAL)RND->getFromIntTo(50, WINSIZE_Y - 50);
		this->setPosition(temp);
		break;
	case BOTTOM:
		temp.X = (REAL)RND->getFromIntTo(50, WINSIZE_X - 50);
		temp.Y = -200;
		this->setPosition(temp);
		break;
	case POSITION:
		break;
	default:
		break;
	}
	_isActive = true;

	
}

void CBlock::ResetPositionRc(RectF rc, REAL x, REAL y, INT whiteTime, bool ispen, REAL penWidth, DWORD time, int timeoffset, int activeTime, float addAngle)
{
	_drection = POSITION;
	this->setPosition(x, y);
	_imgKey = "";
	_rc = rc;
	_whiteTime = whiteTime;
	_isPen = ispen;
	_penWidth = penWidth;
	_time = time;
	_timeOffset = timeoffset;
	_activeTime = activeTime;
	_addAngle = addAngle;
	_isReadyPosition = false;
	_isRandomOffsetTime = true;

	if(whiteTime !=0)_isFlashReady = true;
	else _isFlashReady = false;
	_isActive = true;
	_isFlash = false;
	_angle =0;
	_speed =0;
}

void CBlock::update(int time)
{
	if (!_isActive) return;

	matrixUpdate();

	if (_addAngle != 0) 
	{
		this->addAngle(_addAngle);
	}

	if (time < _time + _whiteTime && _whiteTime !=0) _isFlashReady = true;
	else _isFlashReady = false;

	switch (_drection)
	{
	case LEFT:
		this->setPosition(this->getPosition().X - _speed, this->getPosition().Y);
		break;
	case TOP:
		this->setPosition(this->getPosition().X, this->getPosition().Y - _speed);
		break;
	case RIGHT:
		this->setPosition(this->getPosition().X + _speed, this->getPosition().Y);
		break;
	case BOTTOM:
		this->setPosition(this->getPosition().X, this->getPosition().Y +_speed);
		break;
	case POSITION:
		if (time > _time + _activeTime) 
		{
			this->setIsActive(false);
			this->setIsFrash(false);
		}
		else if(time > _time + _whiteTime+ _timeOffset && _timeOffset!=0)
		{
			this->setIsActive(false);
			this->setIsFrash(false);
			if (_isRandomOffsetTime) 
			{
				this->setTime(RND->getFromIntTo(time, time + _timeOffset+_whiteTime));
			}
			else 
			{
				this->setTime(time + _timeOffset + _whiteTime);
			}
			this->setWhiteTime(0);
		}
		break;
	default:
		break;
	}

	POINT temp;
	temp.x = static_cast<LONG>(getPosition().X);
	temp.y = static_cast<LONG>(getPosition().Y);
	if(!PtInRect(&_outRc, temp))
	{
		if (_isRandomOffsetTime)
		{
			this->setTime(RND->getFromIntTo(time, time + _timeOffset + _whiteTime));
		}
		else
		{
			this->setTime(time + _timeOffset + _whiteTime);
		}
		this->setIsActive(false);
		this->setIsFrash(false);
	}

}

void CBlock::render(Gdiplus::Graphics* g)
{
	if (!_isActive) return;
	g->SetTransform(&getMatrix());
	
	if (_imgKey != "") 
	{
		IMAGEMANAGER->renderForGPbitmap(_imgKey, g,_size);
	}
	else if (_isFlashReady)
	{
		if (_isPen) 
		{
			g->DrawRectangle(&Pen(READY_COLOR, _penWidth), _rc);
		}
		else 
		{
			g->FillRectangle(&SolidBrush(READY_COLOR), _rc);
		}
	}
	else if(_isPen)
	{
		
		if (!_isFlash)
		{
			g->DrawRectangle(&Pen(BASE_COLOR, _penWidth), _rc);
		}
		else
		{
			if (_isExecuteFlash)
			{
				g->DrawRectangle(&Pen(WHITE_COLOR, _penWidth), _rc);
			}
			else
			{
				g->DrawRectangle(&Pen(BASE_COLOR, _penWidth), _rc);
			}
			_isExecuteFlash = !_isExecuteFlash;
		}
	}
	else 
	{
		if (!_isFlash) 
		{
			g->FillRectangle(&SolidBrush(BASE_COLOR), _rc);
		}
		else 
		{
			if (_isExecuteFlash) 
			{
				g->FillRectangle(&SolidBrush(WHITE_COLOR), _rc);
			}
			else 
			{
				g->FillRectangle(&SolidBrush(BASE_COLOR), _rc);
			}
			_isExecuteFlash = !_isExecuteFlash;
		}
	}
	g->SetTransform(&Matrix{1,0,0,1,-400,-400});
	
}


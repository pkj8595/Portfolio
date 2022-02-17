#pragma once

//Gdiplus::setTransform(_m)
class SimpleTranslate
{
private:

	Gdiplus::Matrix	_matrix;
	Gdiplus::PointF	_posi;
	float	_angle;

public:
	SimpleTranslate() : _matrix( 0,0,0,0,0,0 ), _posi(PointF{ 0,0 }), _angle(0){}
	virtual ~SimpleTranslate() {};
	virtual void matrixUpdate();
	//virtual void render(Gdiplus::Graphics &g) = 0;

	void setMatrix(REAL m11,
					REAL m12,
					REAL m21,
					REAL m22,
					REAL dx,
					REAL dy);

	void setAngle(float angle) { _angle = angle; }
	void addAngle(float angle) { _angle += angle; }
	void setPosition(PointF posi) { _posi = posi; }
	void setPosition(REAL x, REAL y) { _posi.X = x; _posi.Y = y; }

	Gdiplus::Matrix& getMatrix() { return _matrix; }
	PointF getPosition() { return _posi; }
	float getAngle() { return _angle; }
};


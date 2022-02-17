#include "Stdafx.h"
#include "SimpleTranslate.h"


void SimpleTranslate::matrixUpdate()
{
	_matrix.SetElements(cosf(_angle), sinf(_angle), -sinf(_angle), cosf(_angle), (_posi.X), (_posi.Y));
}

void SimpleTranslate::setMatrix(REAL m11, REAL m12, REAL m21, REAL m22, REAL dx, REAL dy)
{
	_matrix.SetElements(m11, m12, m21, m22, dx, dy);
}

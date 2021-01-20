#include "StudentMark.h"

StudentMark::StudentMark() 
{
	quiz = 0.0f;
	assignment = 0.0f;
	exam = 0.0f;
	total = 0.0f;
}

void StudentMark::getMark(float q, float a, float e) 
{
	quiz = q;
	assignment = a;
	exam = e;
}

float StudentMark::calculateMark() 
{
	total = quiz + assignment + exam;
	return total;
}

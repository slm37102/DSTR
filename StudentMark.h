#pragma once
class StudentMark
{
	private:
		float quiz, assignment, exam, total;
	public:
		StudentMark();
		void getMark(float, float, float);
		float calculateMark();
};


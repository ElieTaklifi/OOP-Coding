#pragma once
#include "Validator.h"
#include <iostream>

class FacultyValue 
{
public:
	//Constructor & Distructor
	FacultyValue(int faculty = 1) : m_FacultyType(faculty) {};
	~FacultyValue() {};

	//Functions inline
	void setFaculty(int n) { m_FacultyType = n; };
	int getFaculty() const { return m_FacultyType; };

private :
	int m_FacultyType = 0;
};

//Operators global
std::istream & operator >>(std::istream & inp, FacultyValue & fValue);
std::ostream & operator <<(std::ostream & out, const FacultyValue & fValue);
bool operator>= (const FacultyValue & f1, const FacultyValue & f2);
bool operator<=(const FacultyValue & f1, const FacultyValue & f2);
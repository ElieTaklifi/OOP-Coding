#pragma once
#include "Validator.h"

template < class T>
class MinValidator :public Validator <short>
{
public:
	//Constructor & Distructor
	MinValidator(int min): m_Min(min) {} 
	~MinValidator() {};

	//Functions Inline
	bool CheckIfValid(const T & data) { return !(data < m_Min); };
	string getErrorMessage() { return "Error, need to be more than 2"; } ;

private:
	int m_Min;

};
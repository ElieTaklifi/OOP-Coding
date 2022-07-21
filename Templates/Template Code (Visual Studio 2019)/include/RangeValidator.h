#pragma once
#include "Validator.h"

template < class T>
class RangeValidator :public Validator <T>
{
public:
	//Constructor & Distructor
	RangeValidator(T min, T max) : m_Min(min),m_Max(max) {};
	~RangeValidator() {};

	//Functions Inline
	bool CheckIfValid(const T & data) {	return (data >= m_Min && data <= m_Max); };
	string getErrorMessage() { return "Out of range"; };

private:
	T m_Min;
	T m_Max;
};
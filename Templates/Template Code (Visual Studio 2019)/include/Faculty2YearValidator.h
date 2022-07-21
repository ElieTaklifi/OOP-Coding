#pragma once
#include "MultyValidator.h"

enum FacultyType { COMPUTER_SIENCE = 1 , MEDICINE, LITERATURE };

template < class T1,class T2>
class Faculty2YearValidator : public MultyValidator
{
public:
	//Constructor & Distructor
	Faculty2YearValidator(T1* facultyField, T2* yearField)
		: m_facultyField(facultyField), m_yearField(yearField) {};
	~Faculty2YearValidator() {};

	//Functions
	bool checkFormValidator();
	string getErrorMessage();
	void fixFormFields();

private:
	T1 * m_facultyField;
	T2 * m_yearField;
};


//......................................................................
template <typename T1, typename T2>
bool Faculty2YearValidator<T1,T2>::checkFormValidator()
{
	int faculty = m_facultyField->getAnswer().getFaculty();
	int year = m_yearField->getAnswer();

	m_valid = true;
	switch (faculty)
	{
	case(COMPUTER_SIENCE):
		if (year > 4)
			m_valid = false;
		break;

	case(LITERATURE):
		if (year > 3)
			m_valid = false;
		break;

	case(MEDICINE):
		if (year > 7)
			m_valid = false;
		break;
	default :
		return false;
	}
	return m_valid;
}
//......................................................................
template <typename T1, typename T2>
string Faculty2YearValidator<T1, T2>::getErrorMessage()
{
	return "\nFaculty and year don't match\n";
}
//......................................................................
template <typename T1, typename T2>
void Faculty2YearValidator<T1, T2>::fixFormFields()
{
	std::cout << getErrorMessage();
	m_facultyField->setFieldState(false);
	m_yearField->setFieldState(false);
}
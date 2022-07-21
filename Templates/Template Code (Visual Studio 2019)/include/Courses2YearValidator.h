#pragma once
#include "MultyValidator.h"

template < class T1,class T2>
class Courses2YearValidator : public MultyValidator
{
public:
	//Constructor & Distructor
	Courses2YearValidator(T1* courseField,T2* yearField)
		: m_courseField(courseField), m_yearField(yearField) {};
	~Courses2YearValidator() {};

	//Functions
	bool checkFormValidator();
	string getError();
	void fixFormFields();

private:
	T1 * m_courseField;
	T2 * m_yearField;
};

//......................................................................
template <typename T1 , typename T2>
bool Courses2YearValidator<T1, T2>::checkFormValidator()
{
	m_valid = false;
	int course = m_courseField->getAnswer();
	int year = m_yearField->getAnswer();

	if (year < 1 || year > 7 || course < 2 || course > 10)
		return m_valid;

	if ((year == 1 || year == 2) && (course >= 2 && course <= 6))
		m_valid = true;

	if ((year == 3 || year == 4) && (course == 2 && course <= 10))
		m_valid = true;

	if (year >=5 && (course == 2 && course <= 8))
		m_valid = true;

	return m_valid;
}
//......................................................................
template <typename T1, typename T2>
string Courses2YearValidator<T1, T2>::getError()
{
	return "\nCourses and year don't match\n";
}
//......................................................................
template <typename T1, typename T2>
void Courses2YearValidator<T1, T2>::fixFormFields()
{
	std::cout << getError();
	m_courseField->setFieldState(false);
	m_yearField->setFieldState(false);
}
#pragma once
#include "BaseField.h"
#include "Validator.h"

template < class T>
class Field : public BaseField
{
public:
	//Constructor & Distructor
	Field(std::string question) : m_question(question) {};
	~Field() {};

	//Functions
	void fill();
	bool check();
	void print(std::ostream & os);
	
	//Functions Inline
	void addValidator(Validator <T>* validator) { m_FieldValidators.push_back(validator); };
	T getAnswer()const { return m_input; };
	void setAnswer(const T& newAnswer) { m_input = newAnswer; };
	string getQuestion() { return m_question; };

private :
	T m_input;
	std::string m_question;
	std::string m_error;
	vector <Validator <T>*> m_FieldValidators;
};

//**Template Functiuns**

template <typename T>
void Field<T>::fill()
{
	std::cout << m_question;
	std::cin >> m_input;
}


template <typename T>
bool Field<T>::check()
{
	valid = true;
	for (size_t i = 0; i < m_FieldValidators.size(); i++)
		if (!m_FieldValidators[i]->CheckIfValid(m_input))
		{
			m_error = m_FieldValidators[i]->getErrorMessage();
			valid = false;
			return valid;
		}
	return valid;
}


template <typename T>
void Field<T>::print(std::ostream & os)
{

	os << m_question << " = " << m_input;
	if (!valid)
		os << "           " << m_error;
	os << std::endl;
}
// A class that represents a form. A form has many fields

#pragma once
#include <vector>
#include <memory>
#include "BaseField.h"
#include "MultyValidator.h"

using std::vector;

class Form
{
public:
	//Constructor & Distructor
	Form() {};
	~Form() {};

	//Functions
	void addField(BaseField*field);
	void addValidator(MultyValidator* validator);
	void fillForm();
	bool validateForm();
	void printAllField(std::ostream& os) const;

private:
	vector <BaseField *> m_Fields; // Filed vector as data base
	vector <MultyValidator*> m_FormValidators; //Validators data base
	

};

//Operator
std::ostream & operator<<(std::ostream & ostr,const Form & form);

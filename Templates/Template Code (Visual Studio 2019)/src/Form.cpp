#include "Form.h"

void Form::addField(BaseField* field)
{
	m_Fields.push_back(field);
}

void Form::addValidator(MultyValidator* validator)
{
	m_FormValidators.push_back(validator);
}

void Form::fillForm()
{
	for (size_t i = 0; i < m_Fields.size(); i++)
		if(!m_Fields[i]->getFieldState())
			m_Fields[i]->fill();
}

bool Form::validateForm()
{
	bool FormState = true;
	for (size_t i = 0; i < m_Fields.size(); i++)
		if (!m_Fields[i]->check())
			FormState = false;

	if (FormState)
		for (size_t i = 0; i < m_FormValidators.size(); i++)
			if (!m_FormValidators[i]->checkFormValidator())
				FormState = false;

	return FormState;
}

void Form::printAllField(std::ostream & os) const
{

	for (size_t i = 0; i < m_Fields.size(); i++)
		m_Fields[i]->print(os);

	for (size_t i = 0; i < m_FormValidators.size(); i++)
		if (!m_FormValidators[i]->getFormValidState())
			m_FormValidators[i]->fixFormFields();
}

std::ostream & operator<<(std::ostream & ostr, const Form & form)
{
	form.printAllField(ostr);
	return ostr;
}

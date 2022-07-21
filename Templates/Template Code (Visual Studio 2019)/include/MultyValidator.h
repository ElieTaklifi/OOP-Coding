#pragma once

class MultyValidator
{
public:
	//Constructor & Distructor
	MultyValidator() {};
	~MultyValidator() {};

	//Functions virtuals
	virtual bool checkFormValidator() = 0;
	virtual void fixFormFields() = 0;

	//Functions Inline
	bool getFormValidState() { return m_valid; }

protected:
	bool m_valid;
};


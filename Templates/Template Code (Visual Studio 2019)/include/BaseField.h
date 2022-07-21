#pragma once
#include <iostream>

class BaseField
{
public:
	//Constructor & Distructor
	BaseField() {};
	~BaseField() {};

	//Functions virtuals
	virtual void fill() = 0;
	virtual bool check() = 0;
	virtual void print(std::ostream & os) = 0;

	//Functions Inline
	bool getFieldState() { return valid; };
	void setFieldState(bool newState) { valid = newState; };

protected:
	bool valid = false;
};


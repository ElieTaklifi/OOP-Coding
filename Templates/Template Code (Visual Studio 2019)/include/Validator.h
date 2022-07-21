#pragma once
#include <string>

using std::string;

template <class T>
class Validator
{
public:
	//Constructor & Distructor
	Validator() {};
	~Validator() {};

	//Functions virtuals
	virtual string getErrorMessage() = 0;
	virtual bool CheckIfValid(const T & data) = 0;
	
};
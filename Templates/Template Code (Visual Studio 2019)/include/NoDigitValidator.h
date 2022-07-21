#pragma once
#include "Validator.h"
#include <string>

class NoDigitValidator :public Validator <std::string>
{
public:
	//Constructor & Distructor
	NoDigitValidator() {};
	~NoDigitValidator() {};

	bool CheckIfValid(const std::string & name);
	string getErrorMessage() { return "Can't contain digits"; } ;

private:

};


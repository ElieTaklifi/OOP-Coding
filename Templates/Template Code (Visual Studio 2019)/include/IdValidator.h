#pragma once
#include "Validator.h"
#include <cstdint>
#include <string>

using std::string;

class IDValidator :public Validator <uint32_t>
{
public:
	IDValidator() {};
	~IDValidator() {};

	bool CheckIfValid(const uint32_t & id);
	std::string getErrorMessage() {	return "Wrong control digit"; };
};


#pragma once
#include "NoDigitValidator.h"

bool NoDigitValidator::CheckIfValid(const std::string& name)
{
	for (size_t i = 0; i < name.size(); i++)
		if (isdigit(name[i]))
			return false;

	return true;
}
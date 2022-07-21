#include "IdValidator.h"

bool IDValidator::CheckIfValid(const uint32_t& id)
{
	std::string temp = std::to_string(id);

	if (temp.size() != 9)
		return false;

	int counter = 0;
	int incnum;

	for (unsigned int i = 0; i < temp.size(); i++)
	{
		//multiply digit by 1 or 2
		incnum = ((int)temp[i] - 48) * ((i % 2) + 1);
		counter += (incnum > 9) ? incnum - 9 : incnum;
		//sum the digits up and add to counter
	}

	return (counter % 10 == 0);
}

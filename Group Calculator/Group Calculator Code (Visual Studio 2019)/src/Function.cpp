#include "Function.h"

//this is the base class of the program 
// this is an abstract class 
//constructor
Function::Function()
{
}

string Function::addContent(std::vector<int> const& input)
{
	string temp = "{ ";
	for (size_t n = 0; n < input.size(); n++) {
		temp.append(std::to_string(input[n]));
		if (n != input.size() - 1)
			temp.append(", ");
	}
	temp.append(" }");
	return temp;
}

vector<int> Function::fillVec() const
{
	int size, num;
	std::cin >> size;
	auto vec = std::vector<int>();

	for (size_t i = 0; i < size; i++) {
		std::cin >> num;
		vec.push_back(num);
	}
	return vec;
}

string Function::printResult()
{
	return " = " + addContent(m_result);;
}


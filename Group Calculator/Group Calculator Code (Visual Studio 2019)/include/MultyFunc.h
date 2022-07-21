#pragma once
#include "Function.h"

/*Class for operation with multyple operation*/
class MultyFunc : public Function {

public:
	MultyFunc() {};
	virtual ~MultyFunc() = default;

	virtual string printName() = 0;
	virtual void print() = 0;
	virtual vector<int> eval(std::vector<int>& left, std::vector<int>& right) = 0;
	virtual string printHatsava(std::vector<int>& left, std::vector<int>& right) = 0;

protected:
	/*pointers of both sides*/
	std::shared_ptr<Function> m_func1;
	std::shared_ptr<Function> m_func2;
	/*string to print the calcul before the result*/
	std::string m_content;

};
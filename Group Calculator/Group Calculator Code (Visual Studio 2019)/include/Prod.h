#pragma once
#include "MultyFunc.h"

class Prod : public MultyFunc {

public:
	Prod(shared_ptr<Function> func1, shared_ptr<Function> func2);
	virtual ~Prod() = default;

	virtual string printName();
	virtual void print();
	virtual vector<int> eval(std::vector<int>& left, std::vector<int>& right);
	virtual string printHatsava(std::vector<int>& left, std::vector<int>& right);

};
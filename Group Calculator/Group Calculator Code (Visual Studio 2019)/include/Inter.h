#pragma once
#include "MultyFunc.h"

class Inter : public MultyFunc {

public:
	Inter(shared_ptr<Function> func1, shared_ptr<Function> func2);
	virtual ~Inter() = default;

	virtual string printName();
	virtual void print();
	virtual vector<int> eval(std::vector<int>& left, std::vector<int>& right);
	virtual string printHatsava(std::vector<int>& left, std::vector<int>& right);

};
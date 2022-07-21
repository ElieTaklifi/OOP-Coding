#pragma once
#include "SingleFunc.h"

class Sub;

class Sub : public SingleFunc {

public:
	Sub() { m_name = "(A - B)"; };
	virtual ~Sub() = default;

	virtual void print() override;
	virtual string printName() override;
	virtual string printHatsava(std::vector<int>& left, std::vector<int>& right) override;
	virtual vector<int> eval(std::vector<int>& left, std::vector<int>& right) override;

};
#pragma once
#include "SingleFunc.h"

class Crop;

class Crop : public SingleFunc {

public:
	Crop() { m_name = "(A ^ B)"; };
	virtual ~Crop() = default;

	virtual void print() override;
	virtual string printName() override;
	virtual string printHatsava(std::vector<int>& left, std::vector<int>& right) override;
	virtual vector<int> eval(std::vector<int>& left, std::vector<int>& right) override;

};
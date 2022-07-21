#pragma once
#include "SingleFunc.h"

class Add;

class Add : public SingleFunc {

public:
	Add() { m_name = "(A U B)"; };
	virtual ~Add() = default;

	virtual void print() override;
	virtual string printName() override;
	virtual string printHatsava(std::vector<int>& left, std::vector<int>& right) override;
	virtual vector<int> eval(std::vector<int>& left, std::vector<int>& right) override;

};
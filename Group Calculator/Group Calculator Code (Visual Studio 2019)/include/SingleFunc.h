#pragma once
#include "Function.h"

/*Class for basic calcul like add,sub and crop*/

using std::cout;
using std::vector;
using std::shared_ptr;
using std::string;

class SingleFunc;

class SingleFunc : public Function {

public:
	SingleFunc();
	virtual ~SingleFunc() = default;

	virtual string printName() = 0;
	virtual void print() = 0;
	virtual vector<int> eval(std::vector<int>& left, std::vector<int>& right) = 0;
	virtual string printHatsava(std::vector<int>& left, std::vector<int>& right) = 0;
	
protected:
	/*Name of the operation*/
	std::string m_name;
};
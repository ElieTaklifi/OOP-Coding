#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>    // std::sort
#include <string>
#include <memory>

using std::cout;
using std::vector;
using std::shared_ptr;
using std::string;

class Function;

class Function
{
public:
	Function();
	virtual ~Function() = default;

	//virtual functions
	virtual string printName() = 0;
	virtual void print() = 0;
	virtual vector<int> eval(std::vector<int>& left, std::vector<int>& right) = 0;
	virtual string printHatsava(std::vector<int>& left, std::vector<int>& right) = 0;

	//functions
	string addContent(std::vector<int> const& input);
	vector<int> fillVec() const;
	string printResult();

protected:
	/*member saving the result of the operation*/
	std::vector<int> m_result;
};
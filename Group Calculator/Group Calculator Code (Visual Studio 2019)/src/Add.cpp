#include "Add.h"

void Add::print()
{
	/*Filling the both side of the calcul*/
	auto temp_left = std::vector<int>();
	auto temp_right = std::vector<int>();
	temp_left = fillVec();
	temp_right = fillVec();

	/*Calculate the result*/
	m_result = eval(temp_left, temp_right);
	/*print result*/
	std::cout << printHatsava(temp_left, temp_right) << printResult() << "\n";
	return;
}

string Add::printName()
{
	return m_name;
}

/*To print the calcul before the result*/
string Add::printHatsava(std::vector<int>& left, std::vector<int>& right)
{
	std::string m_content;
	m_content.push_back('(');
	m_content.append(addContent(left));
	m_content.append(" U ");
	m_content.append(addContent(right));
	m_content.append(")");

	return m_content;
}

/*Evaluate the result*/
vector<int> Add::eval(std::vector<int>& left, std::vector<int>& right)
{
	/*sort and make unique both sides*/
	sort(left.begin(), left.end());
	auto ret = std::ranges::unique(left);
	left.erase(ret.begin(), ret.end());

	sort(right.begin(), right.end());
	ret = std::ranges::unique(right);
	right.erase(ret.begin(), ret.end());

	auto result = std::vector<int>();
	std::ranges::set_union(left, right, std::back_inserter(result));

	return result;
}
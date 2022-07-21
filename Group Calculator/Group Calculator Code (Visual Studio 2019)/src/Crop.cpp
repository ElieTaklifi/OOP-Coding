#include "Crop.h"

void Crop::print()
{
	auto temp_left = std::vector<int>();
	auto temp_right = std::vector<int>();
	temp_left = fillVec();
	temp_right = fillVec();


	m_result = eval(temp_left, temp_right);
	std::cout << printHatsava(temp_left, temp_right) << printResult() << "\n";
	return;
}

string Crop::printName()
{
	return m_name;
}

string Crop::printHatsava(std::vector<int>& left, std::vector<int>& right)
{
	std::string m_content;
	m_content.push_back('(');
	m_content.append(addContent(left));
	m_content.append(" ^ ");
	m_content.append(addContent(right));
	m_content.append(")");

	return m_content;
}

vector<int> Crop::eval(std::vector<int>& left, std::vector<int>& right)
{
	sort(left.begin(), left.end());
	auto ret = std::ranges::unique(left);
	left.erase(ret.begin(), ret.end());

	sort(right.begin(), right.end());
	ret = std::ranges::unique(right);
	right.erase(ret.begin(), ret.end());

	auto result = std::vector<int>();
	std::ranges::set_intersection(left, right, std::back_inserter(result));

	return result;
}
#include "Prod.h"

Prod::Prod(shared_ptr<Function> func1, shared_ptr<Function> func2)
{
	m_func1 = func1;
	m_func2 = func2;
}

string Prod::printName()
{
	return "(" + m_func1->printName() + " * " + m_func2->printName() + ")";
}

void Prod::print()
{
	auto temp_left = std::vector<int>();
	auto temp_right = std::vector<int>();

	std::cout << printHatsava(temp_left, temp_right) << printResult() << "\n";
	return;
}

string Prod::printHatsava(std::vector<int>& left, std::vector<int>& right)
{
	auto temp_result = std::vector<int>();

	left = fillVec();
	right = fillVec();

	m_content.push_back('(');
	m_result = m_func1->eval(left, right);
	m_content.append(m_func1->printHatsava(left, right));
	m_content.append(" * ");

	left = fillVec();
	right = fillVec();
	temp_result = m_func2->eval(left, right);
	m_content.append(m_func2->printHatsava(left, right));
	m_content.append(")");

	m_result = eval(m_result, temp_result);
	return m_content;
}

vector<int> Prod::eval(std::vector<int>& left, std::vector<int>& right)
{
	auto result = std::vector<int>();

	for (size_t i = 0; i < left.size(); i++) {
		for (size_t j = 0; j < right.size(); j++) {
			result.push_back(left[i] * right[j]);
		}
	}

	sort(result.begin(), result.end());
	auto ret = std::ranges::unique(result);
	result.erase(ret.begin(), ret.end());

	return result;
}

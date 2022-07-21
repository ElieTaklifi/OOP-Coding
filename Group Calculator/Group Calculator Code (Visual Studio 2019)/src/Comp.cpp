#include "Comp.h"

Comp::Comp(shared_ptr<Function> func1, shared_ptr<Function> func2)
{
	m_func1 = func1;
	m_func2 = func2;
}

string Comp::printName()
{
	return "(" + m_func1->printName() + " -> " + m_func2->printName() + ")";
}

void Comp::print()
{
	auto temp_left = std::vector<int>();
	auto temp_right = std::vector<int>();

	std::cout << printHatsava(temp_left, temp_right) << printResult() << "\n";
	return;
}

string Comp::printHatsava(std::vector<int>& left, std::vector<int>& right)
{
	auto temp_result = std::vector<int>();

	left = fillVec();
	right = fillVec();

	m_content.push_back('(');
	m_result = m_func1->eval(left, right);
	m_content.append(m_func1->printHatsava(left, right));
	m_content.append(" -> ");

	/*Use the left side result to calcul the right one*/
	left = m_result;
	right = fillVec();
	temp_result = m_func2->eval(left, right);
	m_content.append(m_func2->printHatsava(left, right));
	m_content.append(")");

	m_result = eval(m_result, temp_result);
	return m_content;
}

vector<int> Comp::eval(std::vector<int>& left, std::vector<int>& right)
{
	return right;
}
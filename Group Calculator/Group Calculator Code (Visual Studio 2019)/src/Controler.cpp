#include "Controler.h"

/*Generate the basic calculator with the three basics operations*/
Controler::Controler() 
{
	m_functions.push_back(std::make_shared<Add>());
	m_functions.push_back(std::make_shared<Crop>());
	m_functions.push_back(std::make_shared<Sub>());
}

/*Manage the progame by analysing input and execute the requests*/
void Controler::run()
{

	static bool end = false;

	std::cout << "List of available set operations:" << std::endl;

	/*Loop untill the user ask to end the program*/
	while (!end) {

		//print the list of functions
		for (size_t i = 0; i < m_functions.size(); i++) {
			std::cout << i << ". " << m_functions[i]->printName() << std::endl;
		}

		//ask for input
		std::cout << std::endl << "Enter command ('help' for the list of available commands): ";
		std::string command;

		std::cin >> command;

		//switch command
		switch ((Command)translate(command)) {

		case help: {
			std::cout << "The available commands are :\n";
			std::cout << "* eval(uate) num ... - compute the result of function #num on the following set(s),\n";
			std::cout << "  each set is prefixed with the count of numbers to read \n";
			std::cout << "* uni(on) num1 num2 - Creates an operation that is the union of operation \n";
			std::cout << "  #num1 and operation #num2\n";
			std::cout << "* inter(section) num1 num2 - Creates an operation that is the intersection \n";
			std::cout << "  of operation #num1 and operation #num2 \n";
			std::cout << "* diff(erence) num1 num2 - Creates an operation that is the difference of \n";
			std::cout << "  operation #num1 and operation #num2 \n";
			std::cout << "* prod(uct) num1 num2 - Creates an operation that returns the product of \n";
			std::cout << "  the items from the results of operation #num1 and operation #num2 \n";
			std::cout << "* comp(osite) num1 num2 - creates an operation that is the composition of \n";
			std::cout << "  operation #num1 and operation #num2 \n";
			std::cout << "* del(ete) num - delete operation #num from the operation list \n";
			std::cout << "* help - print this command list \n";
			std::cout << "* exit - exit the program \n \n";
			break;
			}
		case error: {
			std::cout << "Command not found" << std::endl;
			break;
		}
		case finish: {
			std::cout << "Goodbye!" << std::endl;
			end = true;
			break;
		}
		case eval: {
			int index;
			std::cin >> index;

			if (inVec(index))
				m_functions[index]->print();
			else
				printIndexError(index);
			break;
		}
		case uni: {
			int index1, index2;
			std::cin >> index1 >> index2;

			if (inVec(index1)) {
				if (inVec(index2))
					m_functions.push_back(std::make_shared<Uni>(m_functions[index1], m_functions[index2]));
				else
					printIndexError(index2);
			}
			else
				printIndexError(index1);
			
			break;
		}
		case inter: {
			int index1, index2;
			std::cin >> index1 >> index2;

			if (inVec(index1)) {
				if (inVec(index2))
					m_functions.push_back(std::make_shared<Inter>(m_functions[index1], m_functions[index2]));
				else
					printIndexError(index2);
			}
			else
				printIndexError(index1);

			break;
		}
		case diff: {
			int index1, index2;
			std::cin >> index1 >> index2;

			if (inVec(index1)) {
				if (inVec(index2))
					m_functions.push_back(std::make_shared<Diff>(m_functions[index1], m_functions[index2]));
				else
					printIndexError(index2);
			}
			else
				printIndexError(index1);

			break;
		}
		case prod: {
			int index1, index2;
			std::cin >> index1 >> index2;

			if (inVec(index1)) {
				if (inVec(index2))
					m_functions.push_back(std::make_shared<Prod>(m_functions[index1], m_functions[index2]));
				else
					printIndexError(index2);
			}
			else
				printIndexError(index1);

			break;
		}
		case comp: {
			int index1, index2;
			std::cin >> index1 >> index2;

			if (inVec(index1)) {
				if (inVec(index2))
					m_functions.push_back(std::make_shared<Comp>(m_functions[index1], m_functions[index2]));
				else
					printIndexError(index2);
			}
			else
				printIndexError(index1);

			break;
		}
		case del: {
			/*Delete a function from the list*/
			int index;
			std::cin >> index;
			if (inVec(index))
				m_functions.erase(m_functions.begin() + index);
			else
				printIndexError(index);
			break;
		}

		}

		if (!end)
		{
			std::cout << "\nList of available set operations:" << std::endl;
		}
	}

}

/*This function get the command/input from
the user and compare it to the list of command
that exist;
The function will precisely check is its the same word
*/
int Controler::translate(const std::string& command) {
	
	char request[100];
	strcpy(request, &command[0]);

	if (strncmp(request, "help", 4) == 0) { return help; }
	if (strncmp(request, "eval", 4) == 0) { return eval; }
	if (strncmp(request, "uni", 3) == 0) { return uni; }
	if (strncmp(request, "inter", 5) == 0) { return inter; }
	if (strncmp(request, "diff", 4) == 0) { return diff; }
	if (strncmp(request, "prod", 4) == 0) { return prod; }
	if (strncmp(request, "comp", 4) == 0) { return comp; }
	if (strncmp(request, "del", 3) == 0) { return del; }
	if (strncmp(request, "exit", 4) == 0) { return finish; }

	return error;
}

bool Controler::inVec(double index)
{
	return  index <= m_functions.size() - 1;
}

void Controler::printIndexError(int index)
{
	std::cout << "\nOperation #" << index << " doesn't exist" << std::endl;
	return;
}
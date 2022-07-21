#include "SetCalculator.h"

#include "Union.h"
#include "Intersection.h"
#include "Difference.h"
#include "Product.h"
#include "Comp.h"
#include "Identity.h"

#include <istream>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

namespace rng = std::ranges;

SetCalculator::SetCalculator(std::istream& istr, std::ostream& ostr)
    : m_actions(createActions()), m_operations(createOperations()), m_istr(istr), m_ostr(ostr), m_ptr_istr(&m_istr)
{
    while (m_initSize)
    {
        std::cout << "Please enter maximum number of operations: ";
        resize();
    }
}

void SetCalculator::run()
{
    do
    {
        m_ostr << '\n';
        printOperations();
        m_ostr << "Enter command ('help' for the list of available commands): ";
        const auto action = readAction();

        try {
            runAction(action);
        }

        catch (std::invalid_argument& e)
        {
            handleException(e);
        }

        catch (std::ios_base::failure& e)
        {
            handleException(e);
            cleanBuffer();
        }
        catch (std::length_error& e)
        {
            handleException(e);
            cleanBuffer();
        }

       
    } 
    while (m_running);
}

void SetCalculator::handleException(std::exception& e) const
{
    std::cout << std::endl << "======================================================" << std::endl;
    std::cerr << e.what() << std::endl;
    std::cout << "=======================================================" << std::endl;
}

void SetCalculator::handleFileException(std::exception& e, int& line, bool& stopReading) const
{
    std::cout << "===============================================================" << std::endl;
    std::cout << "There is an error in command: " << line << " // Reason: " << e.what() << std::endl;
    std::cout << "===============================================================" << std::endl;
    stopReading = true;
}

void SetCalculator::readingFileFailedMessage() const
{
    std::cout << "Do you want to countinue reading the file? " << std::endl
              << ">>>> if yes --> enter 'y'" << std::endl
              << ">>>> else --> enter 'n'" << std::endl;
}

void SetCalculator::userChoise(int size, bool currReading)
{
    auto choise = char();
    std::cin >> choise;

    if (choise == 'y' || choise == 'n')
    {
        
        if (choise == 'n')
        {
            if (currReading)
                m_file.close();
            run();
        }
        else if (!currReading)
        {
            for (int i = (int)size; i <= m_operations.size(); i++)
                m_operations.erase(m_operations.end() - 1);
        }
        
    }
    else
        throw std::invalid_argument("The input must be either 'yes' or 'no'. Try again!");
}

void SetCalculator::setSize()
{

    auto num = 0;
    *m_ptr_istr >> num;
    if (m_ptr_istr->fail())
        throw std::ios_base::failure("You should enter a number!");


    if (num >= 3 && num <= 100)
    {
        if (m_maxOperations != 3 && m_operations.size() > num)
        {
            while (true)
            {
                try {
                    wrongResizeMessage(num);
                    userChoise(num, false);
                    break;
                }
                catch (std::invalid_argument& e)
                {
                    handleException(e);
                    cleanBuffer();
                }
            }
        }
        m_maxOperations = (int)num;
        m_initSize = false;
    }
    else
        throw std::out_of_range("The gateLimit must be between 3 to 100");
}

void SetCalculator::wrongResizeMessage(int num) const
{
    std::cout << std::endl;
    std::cout << "There are more operations then: " << num << std::endl;
    std::cout << "Enter 'y' to delete the extra operations" << std::endl;
    std::cout << "Enter 'n' if you wish to exit this command" << std::endl;
}

void SetCalculator::cleanBuffer() const
{
    m_ptr_istr->clear();
    m_ptr_istr->ignore(256, '\n');
}

void SetCalculator::eval()
{
  
    if (auto index = readOperationIndex(); index)
    {
        const auto& operation = m_operations[*index];
        auto inputs = std::vector<Set>();

        for (auto i = 0; i < operation->inputCount(); ++i)
        {
            inputs.push_back(Set(*m_ptr_istr));
        }
        
        if (m_ptr_istr->rdbuf()->in_avail() != 0)
            throw std::length_error("You entered too many argumants!");

        operation->print(m_ostr, inputs);
        m_ostr << " = " << operation->compute(inputs) << '\n';
    }
    
}

void SetCalculator::del()
{
   
    if (auto i = readOperationIndex(); i)
    {
        m_operations.erase(m_operations.begin() + *i);
    }
}

void SetCalculator::help()
{
    m_ostr << "The available commands are:\n";
    for (const auto& action : m_actions)
    {
        m_ostr << "* " << action.command << action.description << '\n';
    }
    m_ostr << '\n';
}

void SetCalculator::exit()
{
    m_ostr << "Goodbye!\n";
    m_running = false;
}

void SetCalculator::read()
{
    bool stopReading = false;
    std::string filename;
    if (!(*m_ptr_istr >> filename))
        throw std::length_error("You should enter a file name !");
   
    std::istream* temp = m_ptr_istr;

    m_file.open(filename);
    if (!m_file.is_open())
        throw std::invalid_argument("Failed to open the file!");
    m_ptr_istr = &m_file;

    int counter = 0;
    while (!(m_file.eof())) {

        try {
            const auto action = readAction();
            counter++;
            runAction(action);

        }
        catch (std::invalid_argument& e)
        {
            handleFileException(e, counter, stopReading);
        }

        catch (std::ios_base::failure& e)
        {
            handleFileException(e, counter, stopReading);
            m_ptr_istr->clear();
            m_ptr_istr->ignore(256, '\n');
        }
        catch (std::length_error& e)
        {
            handleFileException(e, counter, stopReading);
            m_ptr_istr->clear();
            m_ptr_istr->ignore(256, '\n');
        }

        if (stopReading)
        {
            stopReading = false;
            while (true)
            {
                readingFileFailedMessage();
                try {
                    userChoise(0, true);
                    break;
                }
                catch (std::invalid_argument& e)
                {
                    std::cerr << e.what();
                    m_ptr_istr->clear();
                    m_ptr_istr->ignore(256, '\n');
                }
            }
        }   
    }
    m_ptr_istr = temp;
    m_file.close();
}

void SetCalculator::resize()
{
    try{
        setSize();
    }

    catch (std::ios_base::failure& e)
    {
        handleException(e);
        cleanBuffer();
    }
    catch (std::out_of_range& e)
    {
        handleException(e);
    }
    catch (std::invalid_argument& e)
    {
        handleException(e);
    }
    catch (std::length_error& e)
    {
        handleException(e);
    }
}

void SetCalculator::printOperations() const
{
    m_ostr << "List of available set operations:\n";
    for (decltype(m_operations.size()) i = 0; i < m_operations.size(); ++i)
    {
        m_ostr << i << ".\t";
        auto gen = NameGenerator();
        m_operations[i]->print(m_ostr, gen);
        m_ostr << '\n';
    }
    m_ostr << '\n';
}

std::optional<int> SetCalculator::readOperationIndex() const
{
    auto i = 0;
    *m_ptr_istr >> i;
    if (m_ptr_istr->fail())
        throw std::ios_base::failure("You should enter a number!");

    if (i >= m_operations.size())
    {
        std::stringstream errMsg;
        errMsg << "Operation #" << i << " doesn't exist";
        throw std::invalid_argument(errMsg.str().c_str());
        return {};
    }
    return i;
    
}

SetCalculator::Action SetCalculator::readAction() const
{
    auto action = std::string();
    *m_ptr_istr >> action;

    const auto i = std::ranges::find(m_actions, action, &ActionDetails::command);
    if (i != m_actions.end())
    {
        return i->action;
    }

    return Action::Invalid;
}

void SetCalculator::runAction(Action action)
{
    switch (action)
    {
        default:
            throw std::invalid_argument("Unknown enum entry used!");
            break;

        case Action::Invalid:
            throw std::invalid_argument("Command not found");
            break;

        case Action::Eval:         eval();                     break;
        case Action::Union:        binaryFunc<Union>();        break;
        case Action::Intersection: binaryFunc<Intersection>(); break;
        case Action::Difference:   binaryFunc<Difference>();   break;
        case Action::Product:      binaryFunc<Product>();      break;
        case Action::Comp:         binaryFunc<Comp>();         break;
        case Action::Del:          del();                      break;
        case Action::Help:         help();                     break;
        case Action::Exit:         exit();                     break;
        case Action::Read:         read();                     break;
        case Action::Resize:       resize();                   break;
    }
}

SetCalculator::ActionMap SetCalculator::createActions()
{
    return ActionMap
    {
        {
            "eval",
            "(uate) num ... - compute the result of function #num on the "
            "following set(s); each set is prefixed with the count of numbers to"
            " read",
            Action::Eval
        },
        {
            "uni",
            "(on) num1 num2 - Creates an operation that is the union of "
            "operation #num1 and operation #num2",
            Action::Union
        },
        {
            "inter",
            "(section) num1 num2 - Creates an operation that is the "
            "intersection of operation #num1 and operation #num2",
            Action::Intersection
        },
        {
            "diff",
            "(erence) num1 num2 - Creates an operation that is the "
            "difference of operation #num1 and operation #num2",
            Action::Difference
        },
        {
            "prod",
            "(uct) num1 num2 - Creates an operation that returns the product of"
            " the items from the results of operation #num1 and operation #num2",
            Action::Product
        },
        {
            "comp",
            "(osite) num1 num2 - creates an operation that is the composition "
            "of operation #num1 and operation #num2",
            Action::Comp
        },
        {
            "del",
            "(ete) num - delete operation #num from the operation list",
            Action::Del
        },
        {
            "help",
            " - print this command list",
            Action::Help
        },
        {
            "exit",
            " - exit the program",
            Action::Exit
        },
        {
            "read",
            " - read the file",
            Action::Read
        },
        {
            "resize",
            " - resize maximum number of operations",
            Action::Resize
        }
    };
}

SetCalculator::OperationList SetCalculator::createOperations()
{
    return OperationList
    {
        std::make_shared<Union>(std::make_shared<Identity>(), std::make_shared<Identity>()),
        std::make_shared<Intersection>(std::make_shared<Identity>(), std::make_shared<Identity>()),
        std::make_shared<Difference>(std::make_shared<Identity>(), std::make_shared<Identity>())
    };
}

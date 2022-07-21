#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iosfwd>
#include <optional>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <ios>


class Operation;

class SetCalculator
{
public:
    SetCalculator(std::istream& istr, std::ostream& ostr);
    void run();

    void handleException(std::exception& e) const;
    void handleFileException(std::exception& e, int& line, bool& stopReading) const;
    void readingFileFailedMessage() const;
    void userChoise(int size, bool currReading);
    void setSize();
    void wrongResizeMessage(int num) const;
    void cleanBuffer() const;
    

private:
    void eval();
    void del();
    void help();
    void exit();
    void read();
    void resize();

    template <typename FuncType>
    void binaryFunc()
    { 
        if (auto f0 = readOperationIndex(), f1 = readOperationIndex(); f0 && f1)
        {
            m_operations.push_back(std::make_shared<FuncType>(m_operations[*f0], m_operations[*f1]));
        }

    }

    void printOperations() const;

    enum class Action
    {
        Invalid,
        Eval,
        Union,
        Intersection,
        Difference,
        Product,
        Comp,
        Del,
        Help,
        Exit,
        Read,
        Resize,
    };

    struct ActionDetails
    {
        std::string command;
        std::string description;
        Action action;
    };

    using ActionMap = std::vector<ActionDetails>;
    using OperationList = std::vector<std::shared_ptr<Operation>>;

    unsigned int m_maxOperations;
    const ActionMap m_actions;
    OperationList m_operations;
    bool m_running = true;
    bool m_initSize = true;
    std::istream& m_istr;
    std::istream* m_ptr_istr;
    std::ostream& m_ostr;
    std::ifstream m_file;


    std::optional<int> readOperationIndex() const;
    Action readAction() const;
    void runAction(Action action);

    static ActionMap createActions();
    static OperationList createOperations();
    
   
};

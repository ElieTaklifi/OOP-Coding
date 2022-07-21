#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Global.h"

#include "Function.h"

#include "SingleFunc.h"
#include "Add.h"
#include "Sub.h"
#include "Crop.h"

#include "MultyFunc.h"
#include "Uni.h"
#include "Inter.h"
#include "Diff.h"
#include "Prod.h"
#include "Comp.h"

using std::vector;
using std::string;
using std::make_shared;

class Function;

class Controler
{
public:

	Controler();
	void run();
	/*this function will check the validity of the input word with enum in Global.h*/
	int translate(const std::string& command);

private:
	/*Data structure of the list function*/
	std::vector<std::shared_ptr<Function>> m_functions;
	/*Check if input index correct*/
	bool inVec(double index);
	/*Print error index function*/
	void printIndexError(int index);
	
};

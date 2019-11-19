#pragma once
#include "Parser.h"
#include "BlockFactory.h"
#include "BlockMaker.h"
#include "readfile.h"
#include "writefile.h"
#include "grep.h"
#include "sort.h"
#include "replace.h"
#include "dump.h"

class Workflow
{
private:
	std::map<int, std::string> blocks;
	std::list<int> structure;
	std::vector<std::string> inputText;
public:
	Workflow(std::ifstream &input);
};


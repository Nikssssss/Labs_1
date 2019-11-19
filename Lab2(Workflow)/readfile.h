#pragma once
#include "IBlock.h"
#include "BlockMaker.h"
#include <fstream>

class readfile : public IBlock
{
private:
	std::vector<std::string> arguments;
public:
	readfile(std::vector<std::string> arg);
	void execute(std::vector<std::string> &inputText);
	BlockType getType() {
		return IN;
	}
};


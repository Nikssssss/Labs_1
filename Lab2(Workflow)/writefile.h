#pragma once
#include "IBlock.h"
#include "BlockMaker.h"
#include <fstream>

class writefile : public IBlock
{
private:
	std::vector<std::string> arguments;
public:
	writefile(std::vector<std::string> arg);
	writefile();
	void writeOut(std::vector<std::string> arg, std::vector<std::string> &inputText);
	void execute(std::vector<std::string> &inputText);
	BlockType getType() {
		return OUT;
	}
};


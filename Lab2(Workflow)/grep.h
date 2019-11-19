#pragma once
#include "IBlock.h"
#include "BlockMaker.h"

class grep : public IBlock
{
private:
	std::vector<std::string> arguments;
public:
	grep(std::vector<std::string> args);
	void execute(std::vector<std::string> &inputText);
	virtual BlockType getType() {
		return INOUT;
	}
};


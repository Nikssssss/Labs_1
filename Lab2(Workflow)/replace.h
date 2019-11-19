#pragma once
#include "IBlock.h"
#include "BlockMaker.h"

class replace : public IBlock
{
private:
	std::vector<std::string> arguments;
public:
	replace(std::vector<std::string> args);
	void execute(std::vector<std::string> &inputText);
	BlockType getType() {
		return INOUT;
	}
};


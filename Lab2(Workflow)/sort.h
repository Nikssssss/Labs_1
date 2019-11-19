#pragma once
#include "IBlock.h"
#include "BlockMaker.h"
#include <algorithm>

class sort : public IBlock
{
public:
	sort(std::vector<std::string> args);
	void execute(std::vector<std::string> &inputText);
	BlockType getType() {
		return INOUT;
	}
};


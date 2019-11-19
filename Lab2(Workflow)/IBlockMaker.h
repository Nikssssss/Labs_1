#pragma once
#include "IBlock.h"

class IBlockMaker
{
public:
	virtual IBlock* Create(std::vector<std::string> args) const = 0;
};


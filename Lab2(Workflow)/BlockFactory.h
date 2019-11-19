#pragma once
#include <vector>
#include <string>
#include <map>
#include "IBlockMaker.h"

class BlockFactory
{
private:
	std::map<std::string, IBlockMaker*> makers;
public:
	static BlockFactory &Instance();
	void RegisterMaker(const std::string nameOfBlock, IBlockMaker *maker);
	IBlock* Create(std::string nameOfBlock, std::vector<std::string> argumentsOfBlock) const;
};


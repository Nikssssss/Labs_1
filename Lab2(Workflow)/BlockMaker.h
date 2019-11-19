#pragma once
#include "IBlockMaker.h"
#include "BlockFactory.h"

template<typename T>
class BlockMaker : public IBlockMaker
{
public:
	BlockMaker(std::string nameOfBlock) {
		BlockFactory::Instance().RegisterMaker(nameOfBlock, this);
	}

	virtual IBlock* Create(std::vector<std::string> args) const {
		return new T(args);
	}
};

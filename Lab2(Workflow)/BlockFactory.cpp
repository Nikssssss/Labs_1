#include "BlockFactory.h"

BlockFactory &BlockFactory::Instance() {
	static BlockFactory factory;
	return factory;
}

void BlockFactory::RegisterMaker(const std::string nameOfBlock, IBlockMaker* maker) {
	if (makers.find(nameOfBlock) != makers.end()) {
		throw std::exception("Multiple makers for given key!");
	}
	makers[nameOfBlock] = maker;
}

IBlock* BlockFactory::Create(std::string nameOfBlock, std::vector<std::string> argumentsOfBlock) const {
	auto i = makers.find(nameOfBlock);
	if (i == makers.end()) {
		throw std::exception("Unrecognized object type!");
	}
	IBlock *tempBlock = i->second->Create(argumentsOfBlock);
	return tempBlock;
}

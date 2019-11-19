#include "IBlock.h"

IBlock::IBlock() {}

int IBlock::numberOfArguments(std::vector<std::string> args) {
	return args.size();
}

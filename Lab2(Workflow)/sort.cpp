#include "sort.h"
#include "BlockFactory.h"

static BlockMaker<sort> maker("sort");

sort::sort(std::vector<std::string> args){
	if (numberOfArguments(args) != 0)
		throw std::invalid_argument("sort's number of arguments should be 0");
}

void sort::execute(std::vector<std::string> &inputText) {
	std::sort(inputText.begin(), inputText.end());
}

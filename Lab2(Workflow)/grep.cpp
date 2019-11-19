#include "grep.h"
#include "BlockFactory.h"

static BlockMaker<grep> maker("grep");

grep::grep(std::vector<std::string> args){
	if (numberOfArguments(args) != 1)
		throw std::invalid_argument("grep's number of arguments should be 1");
	arguments = args;
}

void grep::execute(std::vector<std::string> &inputText) {
	for (int i = 0; i < inputText.size(); i++) {
		if (inputText[i].find(arguments[0]) == std::string::npos) {
			inputText.erase(inputText.begin() + i);
			i--;
		}
	}
}

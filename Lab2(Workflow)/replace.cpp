#include "replace.h"
#include "BlockFactory.h"

static BlockMaker<replace> maker("replace");

replace::replace(std::vector<std::string> args){
	if (numberOfArguments(args) != 2)
		throw std::invalid_argument("replace's number of arguments should be 2");
	arguments = args;
}

void replace::execute(std::vector<std::string> &inputText) {
	for (int i = 0; i < inputText.size(); i++) {
		int findIndex = 0;
		int subStrInd = inputText[i].find(arguments[0], findIndex);
		while (subStrInd != std::string::npos) {
			inputText[i].replace(subStrInd, arguments[0].length(), arguments[1]);
			findIndex = subStrInd + arguments[0].length();
			subStrInd = inputText[i].find(arguments[0], findIndex);
		}
	}
}

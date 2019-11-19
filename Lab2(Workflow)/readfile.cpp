#include "readfile.h"
#include "BlockFactory.h"

static BlockMaker<readfile> maker("readfile");

readfile::readfile(std::vector<std::string> args) {
	if (numberOfArguments(args) != 1)
		throw std::invalid_argument("readfile's number of arguments should be 1");
	arguments = args;
}

void readfile::execute(std::vector<std::string> &inputText) {
	std::ifstream input(arguments[0]);
	std::string buffer;
	while (std::getline(input, buffer)) {
		inputText.emplace_back(buffer);
		buffer.clear();
	}
	input.close();
}

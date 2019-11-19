#include "dump.h"

static BlockMaker<dump> maker("dump");

dump::dump(std::vector<std::string> args){
	if (numberOfArguments(args) != 1)
		throw std::invalid_argument("dump's number of arguments should be 1");
	arguments = args;
}

void dump::execute(std::vector<std::string> &inputText) {
	writeOut(arguments, inputText);
}
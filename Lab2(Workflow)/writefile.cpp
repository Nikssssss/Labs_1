#include "writefile.h"
#include "BlockFactory.h"

static BlockMaker<writefile> maker("writefile");

writefile::writefile(std::vector<std::string> args) {
	if (numberOfArguments(args) != 1)
		throw std::invalid_argument("writefile's number of arguments should be 1");
	arguments = args;
}

writefile::writefile() {}

void writefile::writeOut(std::vector<std::string> args, std::vector<std::string> &inputText) {
	std::ofstream output(args[0]);
	for (int i = 0; i < inputText.size(); i++) {
		output << inputText[i] << "\n";
	}
	output.close();
}

void writefile::execute(std::vector<std::string> &inputText) {
	writeOut(arguments, inputText);
}

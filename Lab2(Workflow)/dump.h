#pragma once
#include "writefile.h"

class dump : public writefile
{
private:
	std::vector<std::string> arguments;
public:
	dump(std::vector<std::string> args);
	void execute(std::vector<std::string> &inputText);
	BlockType getType() {
		return INOUT;
	}
};


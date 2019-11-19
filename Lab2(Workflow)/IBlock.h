#pragma once
#include <vector>
#include <string>

enum BlockType {IN, INOUT, OUT};

class IBlock
{
public:
	int numberOfArguments(std::vector<std::string> args);
	virtual void execute(std::vector<std::string> &inputText) = 0;
	virtual BlockType getType() = 0;
	IBlock();
};


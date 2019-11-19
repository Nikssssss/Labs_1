#include "Workflow.h"
namespace {
	std::string nameOfBlock(std::string block) {
		std::string tempStr;
		for (int i = 0; i < block.length(); i++) {
			if (block[i] == ' ' && !tempStr.empty())
				return tempStr;
			else if (block[i] != ' ')
				tempStr += block[i];
		}
		return tempStr;
	}

	std::vector<std::string> argumentsOfBlock(std::string block) {
		std::string tempStr;
		std::vector<std::string> tempVector;
		for (int i = 0; i < block.length(); i++) {
			if (block[i] != ' ')
				tempStr += block[i];
			else if (!tempStr.empty() && tempStr != nameOfBlock(block)) {
				tempVector.emplace_back(tempStr);
				tempStr.clear();
			}
			else
				tempStr.clear();
		}
		if (!tempStr.empty() && tempStr != nameOfBlock(block))
			tempVector.emplace_back(tempStr);
		return tempVector;
	}
}

Workflow::Workflow(std::ifstream &input) {
	Parse(blocks, structure, input);
	input.close();

	for (auto i : blocks) {
		std::cout << i.first << ' ' << i.second << std::endl;
	}
	for (auto i : structure) {
		std::cout << i << ' ';
	}

	for (auto it = structure.begin(); it != structure.end(); it++) {
		IBlock *tempBlock = BlockFactory::Instance().Create(nameOfBlock(blocks[*it]), argumentsOfBlock(blocks[*it]));
		switch (tempBlock->getType()) {
		case IN:
			if (it != structure.begin())
				throw std::exception("reading should be executed the first");
			break;
		case INOUT:
			if (it == structure.begin())
				throw std::exception("reading should be executed the first");
			else if (it == prev(structure.end()))
				throw std::exception("writing should be executed the last");
			break;
		case OUT:
			if (it != prev(structure.end()))
				throw std::exception("writing should be executed the last");
			break;
		}
		tempBlock->execute(inputText);
		delete tempBlock;
	}
}

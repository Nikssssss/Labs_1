#include "Parser.h"
#include "BlockFactory.h"

void Parse(std::map<int, std::string> &blocks, std::list<int> &structure, std::ifstream &input) {
	std::string buffer, id;
	std::string block;
	while (std::getline(input, buffer)) {
		if (buffer == "desc") {
			while(1) {
				buffer.clear();
				std::getline(input, buffer);
				if (buffer != "csed") {
					int index;
					for (index = 0; buffer[index] != '='; index++)
						id = id + buffer[index];
					for (int j = index + 1; j < buffer.length(); j++)
						block = block + buffer[j];
					blocks[stoi(id)] = block;
					id.clear();
					block.clear();
					buffer.clear();
				}
				else
					break;
			}
		}
		else {
			for (int i = 0; i < buffer.length(); i++) {
				if (buffer[i] != '-')
					id = id + buffer[i];
				else if (buffer[i + 1] == '>') {
					structure.push_back(stoi(id));
					i++;
					id.clear();
				}
				if (i == buffer.length() - 1)
					structure.push_back(stoi(id));
			}
		}
	}
}



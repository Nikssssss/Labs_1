#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <cctype>

void Parse(std::map<int, std::string> &blocks, std::list<int> &structure, std::ifstream &input);

#pragma once
#include <algorithm>
#include <fstream>
#include <map>
#include <string>
#include <vector>
using namespace std;

class ParseData
{
	map<string, int> container;
	vector<pair<int, string>> newContainer;
public:
	ParseData();
	void ReadAndStore(istream &input);
	void SortData();
	void WriteResult(ostream &output);
private:
	string line;
	int numberOfWords;
};


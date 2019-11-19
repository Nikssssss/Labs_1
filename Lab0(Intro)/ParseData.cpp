#include "ParseData.h"

ParseData::ParseData()
{
	numberOfWords = 0;
}

void ParseData::ReadAndStore(istream &input) {
	int lineLength;
	string tempLine;
	while (getline(input, line)) {
		lineLength = line.length();
		for (int i = 0; i <= lineLength; i++) {
			if (isalpha(line[i]) || isdigit(line[i]))
				tempLine += line[i];
			else {
				if (!tempLine.empty()) {
					container[tempLine]++;
					tempLine.clear();
					numberOfWords++;
				}
			}
		}
	}
}

void ParseData::SortData() {
	for (const auto& el : container) {
		newContainer.emplace_back(make_pair(el.second, el.first));
	}
	sort(newContainer.begin(), newContainer.end());
	reverse(newContainer.begin(), newContainer.end());
}

void ParseData::WriteResult(ostream &output) {
	for (const auto &x : newContainer) {
		output << x.second << "; " << x.first << "; " << ((float)(x.first) / (float)numberOfWords) * 100 << "%" << endl;
	}
}
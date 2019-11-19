#include "ParseData.h"
#include <iostream>
int main(int argc, char **argv) {
	ifstream input(argv[1]);
	ofstream output(argv[2]);
	ParseData pd;
	
	pd.ReadAndStore(input);
	pd.SortData();
	pd.WriteResult(output);

	input.close();
	output.close();

	return 0;
}
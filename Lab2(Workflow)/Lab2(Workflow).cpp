#include "Workflow.h"

int main(int argc, char **argv) {
	std::ifstream input("input.txt");
	try {
		Workflow execution(input);
	}
	catch (std::exception &ex){
		std::cout << ex.what();
	}

	return 0;
}
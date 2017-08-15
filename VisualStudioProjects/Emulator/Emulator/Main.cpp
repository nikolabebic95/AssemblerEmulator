#include <iostream>
#include "CommandLineHelper.h"
#include "FileReader.h"
#include "AddressSpace.h"

int main(int argc, char *argv[]) {

	try {
		auto input = bnssemulator::CommandLineHelper::parse(argc, argv);
		auto data = bnssemulator::FileReader::parse(input);
		bnssemulator::AddressSpace address_space(move(data.sectionTable()), data.symbolTable());
	}
	catch (const std::exception &exception) {
		std::cerr << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unknown exception" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

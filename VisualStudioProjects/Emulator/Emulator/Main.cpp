#include <iostream>
#include "CommandLineHelper.h"
#include "FileReader.h"
#include "AddressSpace.h"
#include "Context.h"
#include "Processor.h"

int main(int argc, char *argv[]) {

	try {
		auto input = bnssemulator::CommandLineHelper::parse(argc, argv);
		auto data = bnssemulator::FileReader::parse(input);
		bnssemulator::Context context(std::move(data));
		bnssemulator::Processor::executeProgram(context);
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

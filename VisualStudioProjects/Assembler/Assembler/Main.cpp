#include <iostream>
#include "FileReader.h"
#include <string>
#include "StringHelper.h"
#include "MicroRiscParser.h"
#include "AssemblerException.h"
#include "FirstPass.h"
#include "SecondPass.h"
#include "FileWriter.h"
#include "CommandLineHelper.h"

int main(int argc, char *argv[]) {
	try {
		auto in_out = bnssassembler::CommandLineHelper::parse(argc, argv);
		auto lines = bnssassembler::FileReader::readAllLines(in_out.first);
		auto parsed = bnssassembler::MicroRiscParser::instance().parse(lines);
		auto first = bnssassembler::FirstPass::execute(parsed);
		auto second = bnssassembler::SecondPass::execute(parsed, std::move(first));
		bnssassembler::FileWriter::write(in_out.second, second);
	}
	catch (bnssassembler::AssemblerException &e) {
		std::cerr << e.message() << std::endl;
		return EXIT_FAILURE;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...) {
		std::cerr << "Unknown error" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

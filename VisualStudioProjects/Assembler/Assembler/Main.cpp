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
		auto in_out = bnss::CommandLineHelper::parse(argc, argv);
		auto lines = bnss::FileReader::readAllLines(in_out.first);
		auto parsed = bnss::MicroRiscParser::instance().parse(lines);
		auto first = bnss::FirstPass::execute(parsed);
		auto second = bnss::SecondPass::execute(parsed, std::move(first));
		bnss::FileWriter::write(in_out.second, second);
	}
	catch (bnss::AssemblerException &e) {
		std::cerr << e.message() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Unknown error" << std::endl;
	}

	return 0;
}

#include <iostream>
#include "FileReader.h"
#include <string>
#include "StringHelper.h"
#include "MicroRiscParser.h"
#include "AssemblerException.h"
#include "FirstPass.h"
#include "SecondPass.h"
#include "FileWriter.h"

int main() {
	try {
		auto lines = bnss::FileReader::readAllLines("test.txt");
		auto parsed = bnss::MicroRiscParser::instance().parse(lines);
		auto first = bnss::FirstPass::execute(parsed);
		auto second = bnss::SecondPass::execute(parsed, std::move(first));
		bnss::FileWriter::write("out.txt", second);
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

#include <iostream>
#include "FileReader.h"
#include <string>
#include "StringHelper.h"
#include "MicroRiscParser.h"
#include "AssemblerException.h"
#include "FirstPass.h"

int main() {
	try {
		auto lines = bnss::FileReader::readAllLines("test.txt");
		auto parsed = bnss::MicroRiscParser::instance().parse(lines);
		auto first = bnss::FirstPass::execute(parsed);
	}
	catch (bnss::AssemblerException &e) {
		std::cout << e.message() << std::endl;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Unknown error" << std::endl;
	}

	return 0;
}

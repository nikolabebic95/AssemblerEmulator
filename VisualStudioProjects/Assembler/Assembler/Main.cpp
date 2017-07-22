#include <iostream>
#include "FileReader.h"
#include <string>
#include "StringHelper.h"
#include "MicroRiscParser.h"
#include "AssemblerException.h"
#include "ExpressionBuilder.h"

int main() {
	try {
		std::cout << "Hello, World!" << std::endl;

		auto lines = bnss::FileReader::readAllLines("test.txt");

		auto parsed = bnss::MicroRiscParser::instance().parse(lines);
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

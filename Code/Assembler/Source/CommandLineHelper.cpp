#include "CommandLineHelper.h"
#include <iostream>
#include "cxxopts.h"

namespace bnssassembler {

	std::pair<std::string, std::string> CommandLineHelper::parse(int argc, char * argv[]) {
		cxxopts::Options options(argv[0], "Assembler\nSystem software\nSchool of Electrical Engineering\nUniversity of Belgrade\nCopyright (c) 2017 Nikola Bebic\n");
		options.add_options()
			("i,input", "Specifies input file", cxxopts::value<std::string>()->default_value("in.ss"))
			("o,output", "Specifies output file", cxxopts::value<std::string>()->default_value("out.out"))
			("h,help", "Prints help");

		options.parse(argc, argv);

		if (options.count("help")) {
			std::cout << options.help() << std::endl;
			exit(0);
		}

		return make_pair(options["input"].as<std::string>(), options["output"].as<std::string>());
	}
}

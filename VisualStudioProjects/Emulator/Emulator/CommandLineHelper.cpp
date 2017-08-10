#include "CommandLineHelper.h"
#include <iostream>
#include "cxxopts.h"

namespace bnssemulator {

	std::string CommandLineHelper::parse(int argc, char * argv[]) {
		cxxopts::Options options(argv[0], "Emulator\nSystem software\nSchool of Electrical Engineering\nUniversity of Belgrade\nCopyright (c) 2017 Nikola Bebic\n");
		options.add_options()
			("i,input", "Specifies input file", cxxopts::value<std::string>()->default_value("out.txt"))
			("h,help", "Prints help");

		options.parse(argc, argv);

		if (options.count("help")) {
			std::cout << options.help() << std::endl;
			exit(0);
		}

		return options["input"].as<std::string>();
	}
}

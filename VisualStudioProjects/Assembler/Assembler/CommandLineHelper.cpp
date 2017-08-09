#include "CommandLineHelper.h"
#include <iostream>
#include "cxxopts.h"

namespace bnss {

	std::pair<std::string, std::string> CommandLineHelper::parse(int argc, char * argv[]) {
		cxxopts::Options options(argv[0], " - command line options");
		options.add_options()
			("i,input", "Specifies input file", cxxopts::value<std::string>()->default_value("in.txt"))
			("o,output", "Specifies output file", cxxopts::value<std::string>()->default_value("out.txt"))
			("h,help", "Prints help");

		options.parse_positional("positional");
		options.parse(argc, argv);

		if (options.count("help")) {
			std::cout << options.help() << std::endl;
			exit(0);
		}

		return make_pair(options["input"].as<std::string>(), options["output"].as<std::string>());
	}
}

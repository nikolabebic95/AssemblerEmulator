#ifndef _command_line_helper_h_
#define _command_line_helper_h_
#include <utility>
#include <string>

namespace bnss {
	
	class CommandLineHelper final {
	public:
		/**
		 * \brief Parses the command line
		 * \param argc Arguments count
		 * \param argv Arguments vector
		 * \return Pair of strings - input and output file names
		 */
		static std::pair<std::string, std::string> parse(int argc, char *argv[]);
	private:
		CommandLineHelper() = delete;
		CommandLineHelper(CommandLineHelper &) = delete;
		void operator=(CommandLineHelper &) = delete;
	};
}

#endif

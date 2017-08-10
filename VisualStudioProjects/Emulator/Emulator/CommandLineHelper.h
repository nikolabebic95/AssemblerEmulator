#ifndef _command_line_helper_h_
#define _command_line_helper_h_
#include <utility>
#include <string>

namespace bnssemulator {

	class CommandLineHelper final {
	public:
		/**
		* \brief Parses the command line
		* \param argc Arguments count
		* \param argv Arguments vector
		* \return Input file name
		*/
		static std::string parse(int argc, char *argv[]);
	private:
		CommandLineHelper() = delete;
		CommandLineHelper(CommandLineHelper &) = delete;
		void operator=(CommandLineHelper &) = delete;
	};
}

#endif

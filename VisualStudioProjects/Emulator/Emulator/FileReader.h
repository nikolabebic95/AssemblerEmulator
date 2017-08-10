#ifndef _file_reader_h_
#define _file_reader_h_
#include "AssemblerOutput.h"
#include <string>

namespace bnssemulator {
	
	class FileReader final {
	public:
		/**
		 * \brief Parses the input file
		 * \param filename Name of the input file
		 * \return Object containing the parsed input file
		 */
		static AssemblerOutput parse(std::string filename);
	private:
		FileReader() = delete;
		FileReader(FileReader &) = delete;
		void operator=(FileReader &) = delete;
	};
}

#endif

#ifndef _file_writer_h_
#define _file_writer_h_
#include <string>
#include "SecondPassData.h"

namespace bnssassembler {
	
	/**
	 * \brief Class used to write the assembler result to a file
	 */
	class FileWriter final {
	public:
		static void write(std::string filename, const SecondPassData &data);
	private:
		FileWriter() = delete;
		FileWriter(FileWriter &) = delete;
		void operator=(FileWriter &) = delete;
	};
}

#endif

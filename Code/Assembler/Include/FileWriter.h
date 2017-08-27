#ifndef _file_writer_h_
#define _file_writer_h_
#include <string>
#include "SecondPassData.h"

namespace bnssassembler {
	
	/**
	 * \brief Utility class used to write the assembler result to a file
	 */
	class FileWriter final {
	public:
		/**
		 * \brief Writes the data to the file
		 * \param filename Name of the file
		 * \param data Data to be written to the file
		 * \throw Throws in case of I/O error
		 */
		static void write(std::string filename, const SecondPassData &data);
	private:
		FileWriter() = delete;
		FileWriter(FileWriter &) = delete;
		void operator=(FileWriter &) = delete;
	};
}

#endif

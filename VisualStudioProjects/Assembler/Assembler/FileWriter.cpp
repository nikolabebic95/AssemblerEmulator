#include "FileWriter.h"
#include "fstream"
#include "SecondPassData.h"
#include <sstream>

namespace bnss {

	void FileWriter::write(std::string filename, const SecondPassData & data) {
		std::ofstream out_file(filename, std::ofstream::binary);
		// TODO: Somehow write the input file name and timestamp
		std::ostringstream stringstream(std::ostringstream::out | std::ostringstream::binary);
		stringstream << data;
		// TODO: Encode the data
		out_file << stringstream.str();
	}
}

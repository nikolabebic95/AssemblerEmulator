#include "FileWriter.h"
#include "fstream"
#include "SecondPassData.h"
#include <sstream>
#include "z85_cpp.h"

namespace bnss {

	void FileWriter::write(std::string filename, const SecondPassData & data) {
		std::ofstream out_file(filename, std::ofstream::binary);
		// TODO: Somehow write the input file name and timestamp
		std::ostringstream stringstream(std::ostringstream::out | std::ostringstream::binary);
		stringstream << data;
		auto encoded = z85::encode_with_padding(stringstream.str());
		out_file << encoded;
	}
}

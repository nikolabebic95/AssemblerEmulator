#include "FileReader.h"
#include "StringHelper.h"
#include "z85_cpp.h"
#include <sstream>

namespace bnssemulator {

	AssemblerOutput FileReader::parse(std::string filename) {
		auto raw_file = StringHelper::fileToString(filename);
		auto decoded = z85::decode_with_padding(raw_file);
		std::stringstream stringstream(decoded);
		AssemblerOutput ret;
		stringstream >> ret;
		return ret;
	}
}

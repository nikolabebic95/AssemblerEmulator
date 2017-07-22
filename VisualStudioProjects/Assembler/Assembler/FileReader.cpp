#include "FileReader.h"
#include "StringHelper.h"

namespace bnss {

	std::vector<std::string> FileReader::readAllLines(std::string filename) {
		auto raw_file = StringHelper::fileToString(filename);
		return StringHelper::split(raw_file, "\n");
	}

}

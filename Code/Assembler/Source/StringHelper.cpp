#include "StringHelper.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdexcept>
#include <iomanip>

namespace bnssassembler {

	std::string StringHelper::fileToString(std::string file_name) {
		std::ifstream file(file_name);
		if (!file.is_open()) {
			throw std::invalid_argument("File " + file_name + " does not exist");
		}

		std::stringstream ss;
		ss << file.rdbuf();
		auto ret = ss.str();
		file.close();
		return ret;
	}

	std::vector<std::string> StringHelper::split(std::string string, std::string delimiters) noexcept {
		std::vector<std::string> ret;

		std::string::size_type last_pos = 0;
		auto pos = string.find_first_of(delimiters, last_pos);

		while (std::string::npos != pos && std::string::npos != last_pos)
		{
			ret.push_back(string.substr(last_pos, pos - last_pos));
			last_pos = pos + 1;
			pos = string.find_first_of(delimiters, last_pos);
		}

		ret.push_back(string.substr(last_pos, pos - last_pos));

		return ret;
	}

	std::string StringHelper::join(std::vector<std::string> strings, std::string delimiter) noexcept {
		switch (strings.size())
		{
		case 0:
			return "";
		case 1:
			return strings[0];
		default:
			std::ostringstream os;
			copy(strings.begin(), strings.end() - 1, std::ostream_iterator<std::string>(os, delimiter.c_str()));
			os << *strings.rbegin();
			return os.str();
		}
	}

	std::string StringHelper::toHexString(unsigned char number) noexcept {
		std::stringstream stream;
		stream << "0x"
			<< std::setfill('0') << std::setw(2)
			<< std::hex << static_cast<unsigned int>(number);
		return stream.str();
	}

	std::string StringHelper::toHexString(signed char number) noexcept {
		std::stringstream stream;
		stream << "0x"
			<< std::setfill('0') << std::setw(2)
			<< std::hex << static_cast<signed int>(number);
		return stream.str();
	}

	bool StringHelper::isAllWhiteSpace(const std::string & string) noexcept {
		for (auto &ch : string) {
			if (!isspace(ch)) return false;
		}

		return true;
	}
}

#include "SectionStartLineParser.h"
#include <regex>
#include "SectionTypeParser.h"
#include "StringHelper.h"
#include "SectionStartToken.h"

namespace bnssassembler {
	
	std::shared_ptr<Token> SectionStartLineParser::parse(const std::string & line, size_t line_number, std::string initial_line) const {
		static std::regex regex("[[:space:]]*[.]([a-zA-Z]*)([.]([0-9][0-9]*))?[[:space:]]*");

		if (!regex_match(line, regex)) {
			return nullptr;
		}

		auto section_name_string = regex_replace(line, regex, "$1");
		auto section_number_string = regex_replace(line, regex, "$3");

		auto section = SectionTypeParser::parse(section_name_string);
		
		if (section_number_string.empty()) {
			return std::make_shared<SectionStartToken>(section, line_number, initial_line);
		}

		auto number = StringHelper::parseNumber<size_t>(section_number_string);
		return std::make_shared<SectionStartToken>(section, line_number, initial_line, number);			
	}
}

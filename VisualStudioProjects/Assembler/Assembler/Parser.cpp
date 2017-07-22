#include "Parser.h"
#include <regex>
#include "StringHelper.h"
#include "LabelToken.h"
#include <algorithm>
#include <string>
#include <iostream>
#include "IncorrectLabelException.h"
#include "CommonRegexes.h"
#include "ParserException.h"

namespace bnss {

	/**
	 * \brief Strips the comment from one line of the file
	 * \param line Line of the file
	 * \param one_line_comment_delimiters Delimiters for one-line comments
	 */
	static void stripComment(std::string &line, std::vector<std::string> one_line_comment_delimiters) {
		auto delimiters = StringHelper::join(one_line_comment_delimiters, "|");
		std::regex regex("(.*?)(" + delimiters + ").*");

		line = regex_replace(line, regex, "$1");
	}

	/**
	 * \brief Extracts the label (if any) from the line
	 * \param line Reference to the line. After this method does not contain the label
	 * \param label_delimiters Strings that separate the label from the rest of the line
	 */
	static std::string extractLabel(std::string &line, std::vector<std::string> label_delimiters) {
		auto delimiters = StringHelper::join(label_delimiters, "|");
		static std::regex regex("(.*)(" + delimiters + ")(.*)");

		if (regex_match(line, regex)) {
			static std::regex label_regex("[[:space:]]*(" + LABEL + ")[[:space:]]*");
			auto ret = regex_replace(line, regex, "$1");
			if (regex_match(ret, label_regex)) {
				ret = regex_replace(ret, label_regex, "$1");
			}
			else {
				throw IncorrectLabelException(ret);
			}

			line = regex_replace(line, regex, "$3");
			return ret;
		}

		return "";

	}

	std::vector<std::shared_ptr<Token>> Parser::parse(std::vector<std::string> body) const {
		std::vector<std::shared_ptr<Token>> ret;

		for (size_t i = 0; i < body.size(); i++) {
			auto &line = body[i];
			auto initial_line = line;

			try {
				// Strip the comments
				stripComment(line, oneLineCommentDelimiters());

				// Extract the label (if it exists) and insert it into the Token vector
				auto label = extractLabel(line, labelDelimiters());
				if (label != "") {
					ret.push_back(std::make_shared<LabelToken>(label, i + 1, initial_line));
				}

				// Skip if the line contains no data
				if (StringHelper::isAllWhiteSpace(line)) {
					continue;
				}

				// Parse the line
				auto token = chain()->tryParse(line, i + 1, initial_line);
				if (token == nullptr) {
					throw MessageException("The line can not be parsed");
				}
				
				ret.push_back(token);

				std::cout << i + 1 << ". " << line << std::endl;
			}
			catch (MessageException &e) {
				throw ParserException(i + 1, initial_line, e.message());
			}
		}

		return ret;
	}
}

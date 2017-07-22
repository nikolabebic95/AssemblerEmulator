#ifndef _line_parser_h_
#define _line_parser_h_

#include "Token.h"
#include <functional>
#include <memory>

namespace bnss {
	
	/**
	 * \brief Chain of command abstract class used for parsing one line of file
	 */
	class LineParser {
	public:
		/**
		 * \brief Tries to parse one line of the file. Calls the next parser in chain if it fails
		 * \param line Line to parse
		 * \param line_number Number of the line that is parsed
		 * \param initial_line Initial line that is parsed
		 * \return Extracted token from line or nullptr if the whole chain failed parsing
		 */
		std::shared_ptr<Token> tryParse(const std::string &line, size_t line_number, std::string initial_line) const noexcept;
		virtual ~LineParser() = default;

		/**
		 * \brief Sets the next parser in the chain of parsers
		 * \param next The next parser
		 */
		void next(std::shared_ptr<LineParser> next) noexcept;

	protected:
		/**
		 * \brief Parses one line of the file. Does not call the next parser in chain
		 * \param line Line to parse
		 * \param line_number Number of the line that is parsed
		 * \param initial_line Initial line that is parsed
		 * \return Extracted token from line or nullptr if the parser failed parsing the line
		 */
		virtual std::shared_ptr<Token> parse(const std::string &line, size_t line_number, std::string initial_line) const noexcept = 0;
	private:
		/**
		 * \brief The next parser in the chain
		 */
		std::shared_ptr<LineParser> next_ = nullptr;
	};
}

#endif

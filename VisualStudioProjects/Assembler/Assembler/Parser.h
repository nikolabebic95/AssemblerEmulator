#ifndef _parser_h_
#define _parser_h_

#include <vector>
#include "Token.h"
#include <memory>
#include "LineParser.h"

namespace bnss {

	/**
	 * \brief Abstract class representing a text parser
	 */
	class Parser {
	public:
		/**
		 * \brief Parses the File into tokens
		 * \param body Collection of all lines in the file
		 * \return Collection of tokens
		 * \throw Throws if the file can not be parsed
		 */
		std::vector<std::shared_ptr<Token>> parse(std::vector<std::string> body) const;

		/**
		 * \brief Virtual destructor needed for polymorphic class
		 */
		virtual ~Parser() = default;
	protected:
		/**
		 * \brief Returns all strings that start the comment to the end of the line
		 * \return Vector of such strings
		 */
		virtual std::vector<std::string> oneLineCommentDelimiters() const noexcept = 0;

		/**
		 * \brief Returns all strings that end the label at the start of the line
		 * \return Vector of such strings
		 */
		virtual std::vector<std::string> labelDelimiters() const noexcept = 0;

		/**
		 * \brief Checks if the parser should stop parsing the file
		 * \param line Line to check
		 */
		virtual bool isEnd(std::string line) const noexcept = 0;

		/**
		 * \brief Returns the first LineParser in chain
		 * \return Pointer to the first parser
		 */
		virtual std::shared_ptr<LineParser> chain() const noexcept = 0;
	};
}

#endif

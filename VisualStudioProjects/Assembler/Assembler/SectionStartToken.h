#ifndef _section_start_token_h_
#define _section_start_token_h_
#include "Token.h"
#include "SectionType.h"

namespace bnss {
	
	/**
	 * \brief Class representing the section start token
	 */
	class SectionStartToken : public Token {
	public:
		/**
		 * \brief Constructs a non-indexed section start token
		 * \param type Type of the section
		 * \param line_number Line number where the section was defined
		 * \param line Line where the section was defined
		 */
		SectionStartToken(SectionType type, size_t line_number, std::string line) noexcept;

		/**
		* \brief Constructs an indexed section start token
		* \param type Type of the section
		* \param line_number Line number where the section was defined
		* \param line Line where the section was defined
		* \param index Index of section
		*/
		SectionStartToken(SectionType type, size_t line_number, std::string line, size_t index) noexcept;
	private:
		SectionType type_;
		bool indexed_ = false;
		size_t index_ = 0;
	};
}

#endif

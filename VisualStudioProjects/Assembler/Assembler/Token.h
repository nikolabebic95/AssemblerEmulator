#ifndef _token_h_
#define _token_h_

#include <string>

namespace bnss {

	/**
	 * \brief Class representing one token of the assembler source file
	 */
	class Token {
	public:
		Token(size_t line_number, std::string line) noexcept;
		virtual ~Token() = default;
	private:
		size_t line_number_;
		std::string line_;
	};
}

#endif

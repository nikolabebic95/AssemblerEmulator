#ifndef _label_token_h_
#define _label_token_h_
#include "Token.h"
#include <string>

namespace bnss {
	
	/**
	 * \brief Class representing the label token
	 */
	class LabelToken : public Token {
	public:
		explicit LabelToken(std::string label, size_t line_number, std::string line) noexcept;
	private:
		std::string label_;
	};
}

#endif

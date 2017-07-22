#include "Token.h"

namespace bnss {

	Token::Token(size_t line_number, std::string line) noexcept : line_number_(line_number), line_(line) {}
}

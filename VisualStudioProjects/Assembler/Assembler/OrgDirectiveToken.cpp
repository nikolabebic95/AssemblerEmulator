#include "OrgDirectiveToken.h"

namespace bnss {

	OrgDirectiveToken::OrgDirectiveToken(MicroRiscExpression expression, size_t line_number, std::string line) noexcept : Token(line_number, line), expression_(expression) {}
}

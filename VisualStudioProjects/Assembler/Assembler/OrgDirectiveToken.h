#ifndef _org_directive_token_h_
#define _org_directive_token_h_
#include "Token.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	class OrgDirectiveToken : public Token {
	public:
		OrgDirectiveToken(MicroRiscExpression expression, size_t line_number, std::string line) noexcept;
	private:
		MicroRiscExpression expression_;
	};
}

#endif

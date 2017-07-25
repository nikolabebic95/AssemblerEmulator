#ifndef _org_directive_token_h_
#define _org_directive_token_h_
#include "Token.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	class OrgDirectiveToken : public Token {
	public:
		OrgDirectiveToken(MicroRiscExpression expression, size_t line_number, std::string line) noexcept;
		void resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		void firstPass(FirstPassData &data) const override;
	private:
		MicroRiscExpression expression_;
	};
}

#endif

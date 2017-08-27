#ifndef _opening_brace_token_h_
#define _opening_brace_token_h_
#include "OperationToken.h"

namespace bnssassembler {

	/**
	* \brief Token class representing the opening brace
	*/
	class OpeningBraceToken : public OperationToken {
	public:
		int inputPriority() const noexcept override;
		int stackPriority() const noexcept override;
		int rank() const noexcept override;
		std::string operation() const noexcept override;
		std::shared_ptr<Expression> create() const override;
	protected:
		std::shared_ptr<ExpressionToken> clone(std::string param) const override;
	};
}

#endif

#ifndef _closing_brace_token_h_
#define _closing_brace_token_h_
#include "OperationToken.h"

namespace bnss {

	/**
	* \brief Token class representing the opening brace
	*/
	class ClosingBraceToken : public OperationToken {
	public:
		int inputPriority() const noexcept override;
		int stackPriority() const noexcept override;
		int rank() const noexcept override;
		std::string operation() const noexcept override;
		std::shared_ptr<Expression> create() const override;
	protected:
		std::shared_ptr<ExpressionToken> clone(std::string param) const override;
		bool isClosingBrace() const noexcept override;
	};
}

#endif

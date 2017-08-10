#ifndef _subtract_token_h_
#define _subtract_token_h_
#include "OperationToken.h"

namespace bnssassembler {
	/**
	* \brief Token class representing the - operation
	*/
	class SubtractToken : public OperationToken {
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

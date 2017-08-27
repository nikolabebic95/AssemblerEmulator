#ifndef _operation_token_h_
#define _operation_token_h_
#include "ExpressionToken.h"

namespace bnssassembler {
	
	/**
	 * \brief Token class representing a math operator
	 */
	class OperationToken : public ExpressionToken {
	public:
		void process(std::list<std::shared_ptr<ExpressionToken>> &output, std::stack<std::shared_ptr<ExpressionToken>> &stack, int &expression_rank) const override;
		virtual std::string operation() const noexcept = 0;
	protected:
		/**
		 * \brief Checks if the operator is the closing brace (closing brace should not be on the stack)
		 * \return Whether the operator is the closing brace
		 */
		virtual bool isClosingBrace() const noexcept;
	};
}

#endif

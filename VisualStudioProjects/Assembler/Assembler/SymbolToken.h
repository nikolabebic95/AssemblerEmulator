#ifndef _symbol_token_h_
#define _symbol_token_h_
#include "ExpressionToken.h"

namespace bnssassembler {
	
	/**
	 * \brief Token class representing a math symbol
	 */
	class SymbolToken : public ExpressionToken {
	public:
		explicit SymbolToken(std::string name) noexcept;
		int inputPriority() const noexcept override;
		int stackPriority() const noexcept override;
		int rank() const noexcept override;
		void process(std::list<std::shared_ptr<ExpressionToken>> &output, std::stack<std::shared_ptr<ExpressionToken>> &stack, int &expression_rank) const override;
		std::shared_ptr<Expression> create() const override;

	protected:
		std::shared_ptr<ExpressionToken> clone(std::string param) const override;

	private:
		std::string name_;

	};
}

#endif

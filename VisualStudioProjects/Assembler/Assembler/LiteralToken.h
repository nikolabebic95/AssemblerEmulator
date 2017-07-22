#ifndef _literal_token_h_
#define _literal_token_h_
#include "ExpressionToken.h"

namespace bnss {
	
	/**
	 * \brief Token class representing a math literal value
	 */
	class LiteralToken : public ExpressionToken {
	public:
		explicit LiteralToken(std::string value) noexcept;
		int inputPriority() const noexcept override;
		int stackPriority() const noexcept override;
		int rank() const noexcept override;
		void process(std::list<std::shared_ptr<ExpressionToken>> &output, std::stack<std::shared_ptr<ExpressionToken>> &stack, int &expression_rank) const override;
		std::shared_ptr<Expression> create() const override;

	protected:
		std::shared_ptr<ExpressionToken> clone(std::string param) const override;

	private:
		int32_t value_;
	};
}

#endif

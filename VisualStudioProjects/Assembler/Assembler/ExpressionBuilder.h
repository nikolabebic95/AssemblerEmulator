#ifndef _expression_builder_h_
#define _expression_builder_h_

#include "MicroRiscExpression.h"
#include "ExpressionToken.h"

namespace bnssassembler {
	
	/**
	 * \brief Utility class used for building math expressions
	 */
	class ExpressionBuilder final {
	public:
		/**
		 * \brief Builds one MicroRiscExpression object from the infix string
		 * \param infix_expression Infix string
		 */
		static MicroRiscExpression build(std::string infix_expression);

		/**
		 * \brief Pops one item from the stack to the postfix output, and updates the rank
		 * \param output Postfix output
		 * \param stack Postfix stack
		 * \param expression_rank Postfix expression rank
		 */
		static void popToPostfix(std::list<std::shared_ptr<ExpressionToken>>& output, std::stack<std::shared_ptr<ExpressionToken>>& stack, int & expression_rank);
	private:
		ExpressionBuilder() = delete;
		ExpressionBuilder(ExpressionBuilder &) = delete;
		void operator=(ExpressionBuilder &) = delete;
	};
}

#endif

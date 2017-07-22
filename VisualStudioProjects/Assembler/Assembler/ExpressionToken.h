#ifndef _expression_token_h_
#define _expression_token_h_
#include <memory>
#include <stack>
#include <list>
#include "Expression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the token found in infix and postfix expressions
	 */
	class ExpressionToken {
	public:
		/**
		 * \brief Gets the input priority of the token
		 * \return Input priority of the token
		 */
		virtual int inputPriority() const noexcept = 0;

		/**
		 * \brief Gets the stack priority of the token
		 * \return Stack priority of the token
		 */
		virtual int stackPriority() const noexcept = 0;

		/**
		 * \brief Gets the rank of the token
		 * \return Rank of the token
		 */
		virtual int rank() const noexcept = 0;

		/**
		 * \brief Processes the current token
		 * \param output Output list of tokens
		 * \param stack Helper stack of tokens
		 * \param expression_rank Rank of the expression
		 */
		virtual void process(std::list<std::shared_ptr<ExpressionToken>> &output, std::stack<std::shared_ptr<ExpressionToken>> &stack, int &expression_rank) const = 0;

		/**
		 * \brief Creates an expression object out of the token
		 * \return Pointer to the expression
		 * \throw Throws if the token has no corresponding expression object
		 */
		virtual std::shared_ptr<Expression> create() const = 0;

		virtual ~ExpressionToken() = default;
	protected:
		/**
		 * \brief Clones the current object, using the string provided
		 * \param param String that will be used to construct the new object
		 * \return Pointer to the cloned object
		 */
		virtual std::shared_ptr<ExpressionToken> clone(std::string param) const = 0;

		ExpressionToken() = default;
	private:
		friend class ExpressionTokenFactory;
	};
}

#endif

#ifndef _expression_h_
#define _expression_h_
#include <cstdint>
#include <memory>
#include <stack>

namespace bnss {
	
	/**
	 * \brief Class representing the math expression
	 */
	class Expression {
	public:
		/**
		 * \brief Evaluates the expression
		 * \throw Throws if the expression has variables or could not be evaluated (for example, division by zero)
		 */
		virtual int32_t value() const = 0;

		/**
		 * \brief Traverses the subtree and sets the value for the symbol
		 * \param symbol Name of the symbol
		 * \param value New value of the symbol
		 * \return Whether the symbol was found and the value was set
		 */
		virtual bool setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept;

		/**
		 * \brief Validates the expression
		 * \return Boolean value indicating whether the expression is correct
		 */
		virtual bool validate() const noexcept;

		/**
		* \brief Tests whether the expression contains a Symbol
		* \return Boolean value indicating whether the expression contains a Symbol
		*/
		virtual bool containsSymbol() const noexcept;

		/**
		 * \brief Counts the symbols in the expression
		 * \return Number of symbols in the expression
		 */
		virtual int symbolCount() const noexcept;
		
		/**
		 * \brief Pushes the children to the stack
		 * \param stack Reference to the stack
		 */
		virtual void pushChildren(std::stack<std::reference_wrapper<std::shared_ptr<Expression>>> &stack) const noexcept;
		virtual ~Expression() = default;
	};
}

#endif

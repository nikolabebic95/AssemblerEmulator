#ifndef _operation_h_
#define _operation_h_
#include "Expression.h"
#include <memory>

namespace bnss {
	
	/**
	 * \brief Class representing the mathematical operation with two operands
	 */
	class Operation : public Expression {
	public:
		int32_t value() const override;
		bool setValue(std::string symbol, std::shared_ptr<Expression> value) noexcept override;
		bool containsSymbol() const noexcept override;
		int symbolCount() const noexcept override;
		void pushChildren(std::stack<std::reference_wrapper<std::shared_ptr<Expression>>> &stack) const noexcept override;

		/**
		 * \brief Sets the left side of the operator
		 * \param left Pointer to the expression on the left side
		 */
		void left(std::shared_ptr<Expression> left) noexcept;

		/**
		 * \brief Sets the right side of the operator
		 * \param right Pointer to the expression on the right side
		 */
		void right(std::shared_ptr<Expression> right) noexcept;

	protected:
		/**
		 * \brief Calculates the value of the subexpression
		 * \param lhs Left side of the operator
		 * \param rhs Right side of the operator
		 * \return Result of the operation
		 * \throw Throws if the expression can not be evaluated (example: division by zero)
		 */
		virtual int32_t calculate(int32_t lhs, int32_t rhs) const = 0;

		/**
		 * \brief Gets the left side of the operator
		 * \return Pointer to the expression on the right side
		 */
		std::shared_ptr<Expression> left() const noexcept;

		/**
		 * \brief Gets the right side of the operator
		 * \return Pointer to the expression on the right side
		 */
		std::shared_ptr<Expression> right() const noexcept;

	private:
		std::shared_ptr<Expression> left_;
		std::shared_ptr<Expression> right_;
	};
}

#endif

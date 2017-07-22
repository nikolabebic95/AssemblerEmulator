#ifndef _micro_risc_expression_h_
#define _micro_risc_expression_h_
#include <memory>
#include "Expression.h"

namespace bnss {
	
	/**
	 * \brief Adapter class for Expression
	 */
	class MicroRiscExpression {
	public:
		/**
		 * \brief Constructs a MicroRiscExpression object
		 * \param expression Pointer to Expression object that this object will adapt
		 */
		explicit MicroRiscExpression(std::shared_ptr<Expression> expression) noexcept;

		/**
		 * \brief Get the value of the expression
		 * \return Value of the expression
		 * \throw Throws if the value can not be calculated
		 */
		int32_t value() const;
	private:
		std::shared_ptr<Expression> expression_;
	};
}

#endif

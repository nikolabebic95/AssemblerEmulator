#include "MicroRiscExpression.h"

namespace bnss {

	MicroRiscExpression::MicroRiscExpression(std::shared_ptr<Expression> expression) noexcept : expression_(expression) {}

	int32_t MicroRiscExpression::value() const {
		return expression_->value();
	}
}

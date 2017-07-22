#ifndef _subtract_operation_h_
#define _subtract_operation_h_
#include "Operation.h"

namespace bnss {

	/**
	* \brief Class implementing the behaviour of the - operator in expressions
	*/
	class SubtractOperation : public Operation {
	public:
		bool containsSymbol() const noexcept override;
		int symbolCount() const noexcept override;
	protected:
		int32_t calculate(int32_t lhs, int32_t rhs) const noexcept override;
	};
}

#endif

#ifndef _divide_operation_h_
#define _divide_operation_h_
#include "Operation.h"

namespace bnss {

	/**
	* \brief Class implementing the behaviour of the / operator in expressions
	*/
	class DivideOperation : public Operation {
	public:
		bool validate() const noexcept override;
	protected:
		int32_t calculate(int32_t lhs, int32_t rhs) const override;
	};
}

#endif

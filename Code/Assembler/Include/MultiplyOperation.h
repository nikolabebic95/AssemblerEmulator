#ifndef _multiply_operation_h_
#define _multiply_operation_h_
#include "Operation.h"

namespace bnssassembler {

	/**
	* \brief Class implementing the behaviour of the * operator in expressions
	*/
	class MultiplyOperation : public Operation {
	public:
		bool validate() const noexcept override;
	protected:
		int32_t calculate(int32_t lhs, int32_t rhs) const noexcept override;
	};
}

#endif

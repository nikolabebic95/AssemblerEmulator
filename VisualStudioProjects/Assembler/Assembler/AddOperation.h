#ifndef _add_operation_h_
#define _add_operation_h_
#include "Operation.h"

namespace bnssassembler {
	
	/**
	 * \brief Class implementing the behaviour of the + operator in expressions
	 */
	class AddOperation : public Operation {
	public:
		std::list<RelocationRecord> generateRelocations() const override;
	protected:
		int32_t calculate(int32_t lhs, int32_t rhs) const noexcept override;
	};
}

#endif

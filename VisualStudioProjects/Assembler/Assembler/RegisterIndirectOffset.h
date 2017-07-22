#ifndef _register_indirect_offset_h_
#define _register_indirect_offset_h_
#include "Operand.h"
#include "Register.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the register indirect operand with offset
	 */
	class RegisterIndirectOffset : public Operand {
	public:
		RegisterIndirectOffset(Register reg, MicroRiscExpression offset) noexcept;
	private:
		Register reg_;
		MicroRiscExpression offset_;
	};
}

#endif

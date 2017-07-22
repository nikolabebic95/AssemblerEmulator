#ifndef _immediate_h_
#define _immediate_h_
#include "Operand.h"
#include "MicroRiscExpression.h"

namespace bnss {
	
	/**
	 * \brief Class representing the immediate operand
	 */
	class Immediate : public Operand {
	public:
		explicit Immediate(MicroRiscExpression value) noexcept;
	private:
		MicroRiscExpression value_;
	};
}

#endif

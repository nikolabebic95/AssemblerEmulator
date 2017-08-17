#include "AluExecuter.h"

namespace bnssemulator {

	void AluExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto &dst = context.getRegister(instruction.register0);
		auto &lhs = context.getRegister(instruction.register1);
		auto &rhs = context.getRegister(instruction.register2);

		execute(dst, lhs, rhs);
	}
}

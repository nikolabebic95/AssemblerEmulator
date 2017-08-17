#include "PopExecuter.h"

namespace bnssemulator {

	void PopExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto &reg = context.getRegister(instruction.register0);
		reg = context.popFromStack();
	}
}

#include "PushExecuter.h"

namespace bnssemulator {

	void PushExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto &reg = context.getRegister(instruction.register0);
		context.pushToStack(reg);
	}
}

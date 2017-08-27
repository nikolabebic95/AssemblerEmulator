#include "CallExecuter.h"

namespace bnssemulator {

	void CallExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto address = context.getOperandAddress(instruction, 0);
		context.jumpToSubroutine(address);
	}
}

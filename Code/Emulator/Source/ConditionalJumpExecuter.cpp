#include "ConditionalJumpExecuter.h"

namespace bnssemulator {

	void ConditionalJumpExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto address = context.getOperandAddress(instruction, 1);
		auto &reg = context.getRegister(instruction.register0);
		
		if (test(reg.negativeFlag(), reg.zeroFlag(), reg.overflowFlag(), reg.carryFlag())) {
			context.jumpTo(address);
		}
	}
}

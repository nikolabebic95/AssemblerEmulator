#include "StoreExecuter.h"
#include "AddressMode.h"
#include "OperandType.h"
#include "MessageException.h"
#include "StringHelper.h"

namespace bnssemulator {

	void StoreExecuter::execute(InstructionBitField instruction, Context & context) const {
		auto &src = context.getRegister(instruction.register0);

		if (instruction.address_mode == REGISTER_DIRECT) {
			auto &dst = context.getRegister(instruction.register1);
			dst = src;
		}
		else {
			auto address = context.getOperandAddress(instruction, 1);
			switch (instruction.type) {
			case REGULAR_BYTE:
				context.addressSpace().set8bitData(address, src);
				break;
			case REGULAR_WORD:
				context.addressSpace().set16bitData(address, src);
				break;
			case REGULAR_DOUBLE_WORD:
				context.addressSpace().set32bitData(address, src);
				break;
			default:
				throw MessageException("Invalid instruction type: " + StringHelper::toHexString(instruction.type));
			}
		}
	}
}

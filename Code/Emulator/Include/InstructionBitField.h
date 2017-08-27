#ifndef _instruction_bit_field_h_
#define _instruction_bit_field_h_
#include <cstdint>

namespace bnssemulator {

	/**
	* \brief Bit field that enables easier manipulation of instructions
	*/
	struct InstructionBitField {
		uint32_t
			operation_code : 8,
			address_mode : 3,
			register0 : 5,
			register1 : 5,
			register2 : 5,
			type : 3,
			unused : 3;
	};
}

#endif

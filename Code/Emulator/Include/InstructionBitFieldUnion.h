#ifndef _instruction_bit_field_union_h_
#define _instruction_bit_field_union_h_
#include "InstructionBitField.h"

namespace bnssemulator {

	/**
	* \brief Union that enables easier manipulation of the instruction bit field
	*/
	union InstructionBitFieldUnion {
		InstructionBitField bit_field;
		uint32_t data;
	};
}

#endif

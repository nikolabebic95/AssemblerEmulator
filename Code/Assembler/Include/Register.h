#ifndef _register_h_
#define _register_h_
// ReSharper disable once CppUnusedIncludeDirective
#include <cstddef>

namespace bnssassembler {

	/**
	 * \brief Number of all purpose registers (excluding PC and SP)
	 */
	const size_t NUM_OF_REGISTERS = 16;

	/**
	 * \brief Enum representing a register
	 */
	enum Register {
		R0 = 0x00,
		R1,
		R2,
		R3,
		R4,
		R5,
		R6,
		R7,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15,
		SP = 0x10,
		PC = 0x11,
		NONE = 0x1F
	};
}

#endif

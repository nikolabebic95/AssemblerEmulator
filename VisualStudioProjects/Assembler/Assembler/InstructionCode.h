#ifndef _instruction_code_h_
#define _instruction_code_h_

namespace bnss {

	/**
	 * \brief Enum representing the instruction code
	 */
	enum InstructionCode {
		INT   = 0x00,
		JMP   = 0x02,
		CALL  = 0x03,
		RET   = 0x01,
		JZ    = 0x04,
		JNZ   = 0x05,
		JGZ   = 0x06,
		JGEZ  = 0x07,
		JLZ   = 0x08,
		JLEZ  = 0x09,
			  
		LOAD  = 0x10,
		STORE = 0x11,

		PUSH  = 0x20,
		POP   = 0x21,

		ADD   = 0x30,
		SUB   = 0x31,
		MUL   = 0x32,
		DIV   = 0x33,
		MOD   = 0x34,
		AND   = 0x35,
		OR    = 0x36,
		XOR   = 0x37,
		NOT   = 0x38,
		ASL   = 0x39,
		ASR   = 0x3A
	};
}

#endif

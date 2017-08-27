#include "InstructionCodeParser.h"
#include <locale>
#include <algorithm>
#include "MessageException.h"

namespace bnssassembler {

	InstructionCode InstructionCodeParser::parse(std::string str) {
		transform(str.begin(), str.end(), str.begin(), tolower);

		if (staticData().map.count(str) == 0) {
			throw MessageException(str + " is not an instruction code");
		}

		return staticData().map[str];
	}

	InstructionCodeParser::InstructionCodeParserStaticData &InstructionCodeParser::staticData() noexcept {
		static InstructionCodeParserStaticData static_data;
		return static_data;
	}

	InstructionCodeParser::InstructionCodeParserStaticData::InstructionCodeParserStaticData() noexcept {
		map["int"]   = INT;
		map["jmp"]   = JMP;
		map["call"]  = CALL;
		map["ret"]   = RET;
		map["jz"]    = JZ;
		map["jnz"]   = JNZ;
		map["jgz"]   = JGZ;
		map["jgez"]  = JGEZ;
		map["jlz"]   = JLZ;
		map["jlez"]  = JLEZ;

		map["load"]  = LOAD;
		map["store"] = STORE;

		map["push"]  = PUSH;
		map["pop"]   = POP;
		
		map["add"]   = ADD;
		map["sub"]   = SUB;
		map["mul"]   = MUL;
		map["div"]   = DIV;
		map["mod"]   = MOD;
		map["and"]   = AND;
		map["or"]    = OR;
		map["xor"]   = XOR;
		map["not"]   = NOT;
		map["asl"]   = ASL;
		map["asr"]   = ASR;
	}
}

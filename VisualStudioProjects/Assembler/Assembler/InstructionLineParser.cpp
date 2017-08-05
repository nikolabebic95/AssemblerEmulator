#include "InstructionLineParser.h"
#include <regex>
#include "InstructionCodeParser.h"
#include "InterruptInstructionParser.h"
#include "NoOperandInstructionParser.h"
#include "ConditionalJumpInstructionParser.h"
#include "UnconditionalJumpInstructionParser.h"
#include "StackInstructionParser.h"
#include "AluInstructionParser.h"
#include "NotInstructionParser.h"
#include "LoadInstructionParser.h"
#include "StoreInstructionParser.h"
#include "MessageException.h"
#include <unordered_map>

namespace bnss {

	/**
	 * \brief Hack to fix the load and store instructions which can have various operands
	 * \param instruction String that should be fixed
	 * \param type Operand type of the instruction that should be set
	 * 
	 * Load and store instructions can have suffices UB, SB, UW, SW, B and W.
	 * Those are still the same instructions with the same instruction codes, but
	 * different operand types. This function fixes the string containing the instruction,
	 * making it look like it is a regular load or store, but sets the operand type to
	 * the specific type. If the instruction is not load or store, this function does nothing
	 */
	static void loadStoreFixup(std::string &instruction, OperandType &type) {
		transform(instruction.begin(), instruction.end(), instruction.begin(), tolower);
		if (instruction == "loadub") {
			instruction = "load";
			type = UNSIGNED_BYTE;
		}
		else if (instruction == "loadsb") {
			instruction = "load";
			type = SIGNED_BYTE;
		}
		else if (instruction == "loaduw") {
			instruction = "load";
			type = UNSIGNED_WORD;
		}
		else if (instruction == "loadsw") {
			instruction = "load";
			type = SIGNED_WORD;
		}
		else if (instruction == "load") {
			type = REGULAR_DOUBLE_WORD;
		}
		else if (instruction == "storeb") {
			instruction = "store";
			type = REGULAR_BYTE;
		}
		else if (instruction == "storew") {
			instruction = "store";
			type = REGULAR_WORD;
		}
		else if (instruction == "store") {
			type = REGULAR_DOUBLE_WORD;
		}
	}

	InstructionLineParser::InstructionLineParser() noexcept {
		instructions_[INT] = std::make_shared<InterruptInstructionParser>();
		instructions_[RET] = std::make_shared<NoOperandInstructionParser>();

		auto uncond_jump = std::make_shared<UndonditionalJumpInstructionParser>();
		instructions_[JMP] = uncond_jump;
		instructions_[CALL] = uncond_jump;

		auto cond_jump = std::make_shared<ConditionalJumpInstructionParser>();
		instructions_[JZ] = cond_jump;
		instructions_[JNZ] = cond_jump;
		instructions_[JGZ] = cond_jump;
		instructions_[JGEZ] = cond_jump;
		instructions_[JLZ] = cond_jump;
		instructions_[JLZ] = cond_jump;

		instructions_[LOAD] = std::make_shared<LoadInstructionParser>();
		instructions_[STORE] = std::make_shared<StoreInstructionParser>();

		auto stack_instruction = std::make_shared<StackInstructionParser>();
		instructions_[PUSH] = stack_instruction;
		instructions_[POP] = stack_instruction;

		auto alu_instruction = std::make_shared<AluInstructionParser>();
		instructions_[ADD] = alu_instruction;
		instructions_[SUB] = alu_instruction;
		instructions_[MUL] = alu_instruction;
		instructions_[DIV] = alu_instruction;
		instructions_[MOD] = alu_instruction;
		instructions_[AND] = alu_instruction;
		instructions_[OR] = alu_instruction;
		instructions_[XOR] = alu_instruction;
		instructions_[ASL] = alu_instruction;
		instructions_[ASR] = alu_instruction;

		instructions_[NOT] = std::make_shared<NotInstructionParser>();
	}

	std::shared_ptr<Token> InstructionLineParser::parse(const std::string &line, size_t line_number, std::string initial_line) const {
		std::regex regex("[[:space:]]*([A-Za-z]*)(.*)[[:space:]]*");
		if (!regex_match(line, regex)) {
			return nullptr;
		}

		auto instruction_code_string = regex_replace(line, regex, "$1");
		auto operands_string = regex_replace(line, regex, "$2");

		auto type = DEFAULT;
		loadStoreFixup(instruction_code_string, type);

		InstructionCode instruction_code;

		try {
			instruction_code = InstructionCodeParser::parse(instruction_code_string);
		}
		catch (MessageException&) {
			return nullptr;
		}

		auto instruction_parser = instructions_.at(instruction_code);
		auto vector_of_operands = instruction_parser->parse(operands_string);
		return std::make_shared<InstructionToken>(line_number, initial_line, instruction_code, vector_of_operands, type);
	}
}

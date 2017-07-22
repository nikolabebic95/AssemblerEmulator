#ifndef _instruction_code_parser_h_
#define _instruction_code_parser_h_
#include <unordered_map>
#include "InstructionCode.h"

namespace bnss {
	
	/**
	 * \brief Utility class used for parsing instruction codes
	 */
	class InstructionCodeParser final {
	public:
		/**
		 * \brief Parses the instruction code
		 * \param str String representing the instruction code
		 * \return Instruction code
		 * \throw Throws if the instruction code is not valid
		 */
		static InstructionCode parse(std::string str);
	private:
		struct InstructionCodeParserStaticData {
			std::unordered_map<std::string, InstructionCode> map;
			InstructionCodeParserStaticData() noexcept;
		};

		static InstructionCodeParserStaticData &staticData() noexcept;

		InstructionCodeParser() = delete;
		InstructionCodeParser(InstructionCodeParser &) = delete;
		void operator=(InstructionCodeParser &) = delete;
	};
}

#endif

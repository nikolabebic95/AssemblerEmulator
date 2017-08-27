#ifndef _instruction_parser_h_
#define _instruction_parser_h_
#include <memory>
#include "InstructionToken.h"
#include "OperandParser.h"

namespace bnssassembler {
	
	/**
	 * \brief Abstract lass used for parsing one instruction
	 */
	class InstructionParser {
	public:
		/**
		 * \brief Parses the instruction
		 * \param str String representing the instruction
		 * \return Vector of operands in the instruction
		 * \throw Throws if it fails parsing
		 */
		std::vector<std::shared_ptr<Operand>> parse(std::string str) const;
		
		/**
		 * \brief Abstract destructor so the class is abstract
		 */
		virtual ~InstructionParser() = 0;
	protected:
		/**
		 * \brief The chains of operand parsers for all operands
		 */
		std::vector<std::shared_ptr<OperandParser>> operands_;
	};
}

#endif

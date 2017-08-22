#ifndef _operand_parser_h_
#define _operand_parser_h_
#include <memory>
#include "Operand.h"
#include <string>

namespace bnssassembler {
	
	/**
	 * \brief Chain of command class used to parse operands of the instructions
	 */
	class OperandParser {
	public:
		/**
		 * \brief Tries to parse one operand. Calls the next parser in the chain if it fails
		 * \param str Operand which should be parsed
		 * \return Pointer to the operand or nullptr, if the whole chain failed parsing
		 * \throw Throws if the chain fails but identifies the error
		 */
		std::shared_ptr<Operand> tryParse(std::string str) const;

		/**
		 * \brief Sets the next parser in the chain
		 * \param next Next parser in the chain
		 */
		void next(std::shared_ptr<OperandParser> next) noexcept;
		virtual ~OperandParser() = default;
	protected:
		/**
		 * \brief Parses one operand. Does not call the next parser if it fails
		 * \param str Operand which should be parsed
		 * \return Pointer to the operand or nullptr, if the parser failed parsing
		 * \throw Throws if the parser fails but identifies the error
		 */
		virtual std::shared_ptr<Operand> parse(std::string str) const = 0;
	private:
		/**
		 * \brief The next parser in the chain
		 */
		std::shared_ptr<OperandParser> next_;
	};
}

#endif

#ifndef _instruction_line_parser_h_
#define _instruction_line_parser_h_
#include "LineParser.h"
#include "InstructionCode.h"
#include "InstructionParser.h"
#include <memory>
#include <unordered_map>

namespace bnssassembler {

	/**
	 * \brief Class used for parsing instructions
	 */
	class InstructionLineParser : public LineParser {
	public:
		/**
		 * \brief Constructs an InstructionLineParser object
		 */
		InstructionLineParser() noexcept;
	protected:
		std::shared_ptr<Token> parse(const std::string &line, size_t line_number, std::string initial_line) const override;
	private:
		std::unordered_map<InstructionCode, std::shared_ptr<InstructionParser>> instructions_;
	};
}

#endif

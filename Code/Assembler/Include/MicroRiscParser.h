#ifndef _micro_risc_parser_h_
#define _micro_risc_parser_h_
#include "Parser.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the parser for the MicroRISC assembly
	 */
	class MicroRiscParser : public Parser {
	public:
		/**
		 * \brief Static method for getting the singleton object
		 * \return Reference to the singleton MicroRiscParser object
		 */
		static MicroRiscParser &instance() noexcept;
	protected:
		std::vector<std::string> oneLineCommentDelimiters() const noexcept override;
		std::vector<std::string> labelDelimiters() const noexcept override;
		bool isEnd(std::string line) const noexcept override;
		std::shared_ptr<LineParser> chain() const noexcept override;
	private:
		std::shared_ptr<LineParser> head_;

		MicroRiscParser();
		MicroRiscParser(MicroRiscParser &) = delete;
		void operator=(MicroRiscParser &) = delete;
	};
}

#endif

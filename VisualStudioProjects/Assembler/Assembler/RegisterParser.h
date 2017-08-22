#ifndef _register_parser_h_
#define _register_parser_h_
#include "Register.h"
#include <unordered_map>

namespace bnssassembler {
	
	/**
	 * \brief Utility class used for parsing registers
	 */
	class RegisterParser final {
	public:
		/**
		 * \brief Parses the register
		 * \param str String representing the register
		 * \return Register
		 * \throw Throws if the register is not valid
		 */
		static Register parse(std::string str);
	private:
		struct RegisterParserStaticData {
			std::unordered_map<std::string, Register> map;
			RegisterParserStaticData() noexcept;
		};

		static RegisterParserStaticData &staticData() noexcept;

		RegisterParser() = delete;
		RegisterParser(RegisterParser &) = delete;
		void operator=(RegisterParser &) = delete;
	};
}

#endif

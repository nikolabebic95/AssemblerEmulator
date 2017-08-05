#ifndef _data_definition_token_h_
#define _data_definition_token_h_
#include <vector>
#include "Data.h"
#include "Token.h"

namespace bnss {
	
	/**
	 * \brief Class representing the data definition token
	 */
	class DataDefinitionToken : public Token {
	public:
		DataDefinitionToken(std::vector<Data> data, size_t line_number, std::string line) noexcept;
		void resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept override;
		void firstPass(FirstPassData &data) const override;
		void secondPass(SecondPassData &data) const override;
		void resolveSymbolTable(const SymbolTable &symbol_table) noexcept override;
		void resolveImports(std::unordered_set<std::string> imported_symbols) noexcept override;
	private:
		std::vector<Data> data_;
		
		/**
		 * \brief Gets the size of the data defined with this token
		 * \return Size of the data defined
		 */
		size_t dataSize() const noexcept;
	};
}

#endif

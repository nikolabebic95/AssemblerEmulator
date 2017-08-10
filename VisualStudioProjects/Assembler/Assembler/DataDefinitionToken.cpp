#include "DataDefinitionToken.h"
#include "DataTypeParser.h"
#include "SecondPassData.h"
#include "MessageException.h"

namespace bnssassembler {

	DataDefinitionToken::DataDefinitionToken(std::vector<Data> data, size_t line_number, std::string line) noexcept : Token(line_number, line), data_(data) {}

	void DataDefinitionToken::resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			for (auto &data : data_) {
				if (data.initialized()) {
					data.value().setValue(symbol.name(), symbol.expression());
				}

				data.count().setValue(symbol.name(), symbol.expression());
			}
		}
	}

	void DataDefinitionToken::firstPass(FirstPassData &data) const {
		data.incLocationCounter(dataSize());
	}

	void DataDefinitionToken::secondPass(SecondPassData & data) const {
		for (auto &data_definition : data_) {
			if (data_definition.initialized()) {
				if (data.currentSectionType() != DATA && data.currentSectionType() != RODATA) {
					throw MessageException("Initialized values can only exist in DATA and RODATA sections");
				}

				for (auto i = 0; i < data_definition.count().value(); i++) { 
					switch (data_definition.type()) {
					case DOUBLE_WORD: 
						data.addData(static_cast<uint32_t>(data_definition.value().value()), data_definition.value().generateRelocations());
						break;
					case WORD: 
						data.addData(static_cast<uint16_t>(data_definition.value().value()), data_definition.value().generateRelocations());
						break;
					case BYTE: 
						data.addData(static_cast<uint8_t>(data_definition.value().value()), data_definition.value().generateRelocations());
						break;
					default: 
						throw MessageException("Data type not implemented");
					}
				}
			}
			else {
				if (data.currentSectionType() != BSS) {
					throw MessageException("Uninitialized values can only exist in the BSS section");
				}
			}
		}
	}

	void DataDefinitionToken::resolveSymbolTable(const SymbolTable &symbol_table) noexcept {
		for (auto &data: data_) {
			if (data.initialized()) {
				data.value().resolveSymbolTable(symbol_table);
			}

			data.count().resolveSymbolTable(symbol_table);
		}
	}

	void DataDefinitionToken::resolveImports(std::unordered_set<std::string> imported_symbols) noexcept {
		for (auto &data: data_) {
			if (data.initialized()) {
				data.value().resolveImports(imported_symbols);
			}

			data.count().resolveImports(imported_symbols);
		}
	}

	size_t DataDefinitionToken::dataSize() const noexcept {
		size_t ret = 0;

		for (auto &data : data_) {
			ret += data.count().value() * DataTypeParser::size(data.type());
		}
		
		return ret;
	}
}

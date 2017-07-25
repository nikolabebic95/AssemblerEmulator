#include "DataDefinitionToken.h"
#include "DataTypeParser.h"

namespace bnss {

	DataDefinitionToken::DataDefinitionToken(std::vector<Data> data, size_t line_number, std::string line) noexcept : Token(line_number, line), data_(data) {}

	void DataDefinitionToken::resolveSymbolDefinitions(std::unordered_set<SymbolDefinition> symbols) noexcept {
		for (auto &symbol : symbols) {
			for (auto &data : data_) {
				data.value().setValue(symbol.name(), symbol.expression());
				data.count().setValue(symbol.name(), symbol.expression());
			}
		}
	}

	void DataDefinitionToken::firstPass(FirstPassData &data) const {
		data.incLocationCounter(dataSize());
	}

	size_t DataDefinitionToken::dataSize() const noexcept {
		size_t ret = 0;

		for (auto &data : data_) {
			ret += data.count().value() * DataTypeParser::size(data.type());
		}
		
		return ret;
	}
}

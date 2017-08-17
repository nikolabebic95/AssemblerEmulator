#include "DataTypeParser.h"
#include <algorithm>
#include <locale>
#include "InvalidDataTypeException.h"

namespace bnssassembler {

	DataType DataTypeParser::parse(std::string str) {
		transform(str.begin(), str.end(), str.begin(), tolower);

		if (staticData().map.count(str) == 0) {
			throw InvalidDataTypeException(str);
		}

		return staticData().map[str];
	}

	size_t DataTypeParser::size(DataType data) {
		switch (data) {
		case BYTE: return 1;
		case WORD: return 2;
		case DOUBLE_WORD: return 4;
		default: throw MessageException("DataType not yet implemented");
		}
	}

	DataTypeParser::DataTypeParserStaticData::DataTypeParserStaticData() {
		map["db"] = BYTE;
		map["dw"] = WORD;
		map["dd"] = DOUBLE_WORD;
	}

	DataTypeParser::DataTypeParserStaticData & DataTypeParser::staticData() noexcept {
		static DataTypeParserStaticData static_data;
		return static_data;
	}
}

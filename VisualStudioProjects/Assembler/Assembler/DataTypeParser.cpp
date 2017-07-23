#include "DataTypeParser.h"
#include <algorithm>
#include <locale>
#include "InvalidDataTypeException.h"

namespace bnss {

	DataType DataTypeParser::parse(std::string str) {
		transform(str.begin(), str.end(), str.begin(), tolower);

		if (staticData().map.count(str) == 0) {
			throw InvalidDataTypeException(str);
		}

		return staticData().map[str];
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

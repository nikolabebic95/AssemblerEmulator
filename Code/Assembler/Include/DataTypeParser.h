#ifndef _data_type_parser_h_
#define _data_type_parser_h_
#include "DataType.h"
#include <unordered_map>

namespace bnssassembler {
	
	/**
	 * \brief Utility class used for parsing data types
	 */
	class DataTypeParser final {
	public:
		/**
		 * \brief Parses the datatype from string
		 * \param str String containing the data type
		 * \return Parsed data type
		 */
		static DataType parse(std::string str);

		/**
		 * \brief Returns the size of the data type in bytes
		 * \param data DataType
		 */
		static size_t size(DataType data);
	private:
		struct DataTypeParserStaticData {
			std::unordered_map<std::string, DataType> map;
			DataTypeParserStaticData();
		};

		static DataTypeParserStaticData &staticData() noexcept;

		DataTypeParser() = delete;
		DataTypeParser(DataTypeParser &) = delete;
		void operator=(DataTypeParser &) = delete;
	};
}

#endif

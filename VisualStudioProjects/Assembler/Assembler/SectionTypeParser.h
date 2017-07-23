#ifndef _section_type_parser_h_
#define _section_type_parser_h_
#include "SectionType.h"
#include <string>
#include <unordered_map>

namespace bnss {
	
	/**
	 * \brief Utility class representing the parser for the section types
	 */
	class SectionTypeParser final {
	public:
		/**
		 * \brief Parses the section type
		 * \param type String representing the section
		 * \return SectionType enum
		 * \throw Throws if the section is invalid
		 */
		static SectionType parse(std::string type);
	private:
		struct SectionTypeParserData {
			std::unordered_map<std::string, SectionType> map;
			SectionTypeParserData();
		};

		static SectionTypeParserData &staticData() noexcept;
	};
}

#endif

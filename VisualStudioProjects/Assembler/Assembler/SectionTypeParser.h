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

		/**
		 * \brief Converts a SectionType to string
		 * \param type SectionType object
		 * \return String representation of the type
		 */
		static std::string toString(SectionType type) noexcept;
	private:
		struct SectionTypeParserData {
			std::unordered_map<std::string, SectionType> map;
			std::unordered_map<SectionType, std::string> reverse;
			SectionTypeParserData();
		};

		static SectionTypeParserData &staticData() noexcept;
	};
}

#endif

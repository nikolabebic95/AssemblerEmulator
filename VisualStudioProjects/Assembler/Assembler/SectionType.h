#ifndef _section_type_h_
#define _section_type_h_
#include <cstdint>
#include <functional>

namespace bnssassembler {

	/**
	 * \brief Enum representing the type of the section
	 */
	enum SectionType : int8_t {
		TEXT = 0,	/**< Text section */
		DATA,		/**< Data section */
		RODATA,		/**< Read-only data section */
		BSS			/**< Block started by symbol section */
	};
}

namespace std {
	template <> struct hash<bnssassembler::SectionType> {
		size_t operator()(const bnssassembler::SectionType & type) const;
	};

	inline size_t hash<bnssassembler::SectionType>::operator()(const bnssassembler::SectionType & type) const {
		return hash<int8_t>()(static_cast<int8_t>(type));
	}
}

#endif

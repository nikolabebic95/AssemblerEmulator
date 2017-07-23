#ifndef _section_type_h_
#define _section_type_h_

namespace bnss {

	/**
	 * \brief Enum representing the type of the section
	 */
	enum SectionType {
		TEXT,		/**< Text section */
		DATA,		/**< Data section */
		RODATA,		/**< Read-only data section */
		BSS			/**< Block started by symbol section */
	};
}

#endif

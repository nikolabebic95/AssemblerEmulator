#ifndef _assembler_output_h_
#define _assembler_output_h_
#include <istream>
#include "SectionData.h"
#include "SymbolData.h"
#include <unordered_set>
#include <vector>
#include <unordered_map>

namespace bnssemulator {
	
	class AssemblerOutput {
	public:
		/**
		 * \brief Loads the object from stream
		 * \param is Input stream
		 * \param data Reference to the object that should be loaded
		 * \return Input stream
		 */
		friend std::istream &operator>>(std::istream &is, AssemblerOutput &data);
		
		/**
		 * \brief Gets the section table
		 * \return Section table
		 */
		std::vector<SectionData> &sectionTable() noexcept;

		/**
		 * \brief Gets the section table
		 * \return Section table
		 */
		const std::vector<SectionData> &sectionTable() const noexcept;

	private:
		std::unordered_set<std::string> imported_symbols_;
		std::vector<SectionData> section_table_;
		std::unordered_map<std::string, SymbolData> symbol_table_;
	};
}

#endif

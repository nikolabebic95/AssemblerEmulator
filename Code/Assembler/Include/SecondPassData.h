#ifndef _second_pass_data_h_
#define _second_pass_data_h_
#include "FirstPassData.h"
#include "SectionType.h"

namespace bnssassembler {
	
	/**
	 * \brief Class representing the data that will be updated during the second pass
	 */
	class SecondPassData {
	public:
		/**
		 * \brief Constructs the object
		 * \param first_pass_data Data generated by the first pass
		 */
		explicit SecondPassData(FirstPassData &&first_pass_data) noexcept;

		/**
		 * \brief Increasses the current section counter
		 */
		void nextSection() noexcept;

		/**
		 * \brief Check if the ORG address is valid
		 */
		bool orgValid() const noexcept;

		/**
		 * \brief Check whether the symbol exists in the symbol table
		 */
		bool contains(std::string symbol) const noexcept;

		/**
		 * \brief Inserts an imported symbol into the set
		 * \param symbol Symbol to be imported
		 */
		void insertImported(std::string symbol);

		/**
		 * \brief Exports a symbol
		 * \param symbol Symbol to be exported
		 */
		void exportSymbol(std::string symbol);

		/**
		 * \brief Gets the current section type
		 * \return Current section type
		 */
		SectionType currentSectionType() const noexcept;

		/**
		* \brief Adds 8 bits of data to the current section
		* \param data Data to be addded
		* \param relocations List of relocation records for the data
		*/
		void addData(uint8_t data, std::list<RelocationRecord> relocations);

		/**
		* \brief Adds 16 bits of data to the current section
		* \param data Data to be addded
		* \param relocations List of relocation records for the data
		*/
		void addData(uint16_t data, std::list<RelocationRecord> relocations);

		/**
		* \brief Adds 32 bits of data to the current section
		* \param data Data to be addded
		* \param relocations List of relocation records for the data
		*/
		void addData(uint32_t data, std::list<RelocationRecord> relocations);

		/**
		 * \brief Sets the ORG address
		 * \param address ORG address
		 */
		void org(uint32_t address);

		/**
		* \brief Gets the symbol table
		* \return Symbol table
		*/
		SymbolTable &symbolTable() noexcept;

		/**
		 * \brief Gets the symbol table
		 * \return Symbol table
		 */
		const SymbolTable &symbolTable() const noexcept;

		/**
		 * \brief Gets the collection of imported symbols
		 * \return Collection of imported symbols
		 */
		std::unordered_set<std::string> &importedSymbols();

		/**
		* \brief Gets the collection of imported symbols
		* \return Collection of imported symbols
		*/
		const std::unordered_set<std::string> &importedSymbols() const;

		/**
		 * \brief Gets the index of the current section
		 */
		size_t currentSectionIndex() const noexcept;

		/**
		 * \brief Gets the current offset inside the current section
		 */
		size_t currentSectionOffset() const noexcept;

		/**
		 * \brief Writes the content of the object to a stream
		 * \param os Stream where the content will be written
		 * \param data Data that will be written
		 */
		friend std::ostream &operator<<(std::ostream &os, const SecondPassData &data);
	private:
		std::unordered_set<std::string> imported_symbols_;
		SymbolTable symbol_table_;
		SectionTable section_table_;

		int32_t org_address_ = 0;
		bool org_valid_ = false;
	};
}

#endif

#ifndef _address_space_h_
#define _address_space_h_
#include "Segment.h"
#include <map>
#include "SectionData.h"
#include "InstructionBitField.h"
#include "SymbolData.h"
#include <unordered_map>

namespace bnssemulator {
	
	/**
	 * \brief Class representing the address space of the emulator
	 */
	class AddressSpace : std::map<uint32_t, Segment> {
	public:
		/**
		 * \brief Constructs an address space from the section table
		 * \param section_table Section table
		 */
		explicit AddressSpace(std::vector<SectionData> &&section_table, const std::unordered_map<std::string, SymbolData> symbol_table);

		/**
		 * \brief Gets the instruction at the specified address
		 * \param address Address
		 * \return Instruction
		 */
		InstructionBitField getInstruction(uint32_t address) const;

		/**
		 * \brief Gets 8 bits of data at the specified address
		 * \param address Address
		 * \return Data
		 */
		uint8_t get8bitData(uint32_t address) const;

		/**
		* \brief Gets 16 bits of data at the specified address
		* \param address Address
		* \return Data
		*/
		uint16_t get16bitData(uint32_t address) const;

		/**
		* \brief Gets 32 bits of data at the specified address
		* \param address Address
		* \return Data
		*/
		uint32_t get32bitData(uint32_t address) const;

		/**
		* \brief Sets 8 bits of data at the specified address
		* \param address Address
		* \param data Data
		*/
		void set8bitData(uint32_t address, uint8_t data);

		/**
		* \brief Sets 16 bits of data at the specified address
		* \param address Address
		* \param data Data
		*/
		void set16bitData(uint32_t address, uint16_t data);

		/**
		* \brief Sets 32 bits of data at the specified address
		* \param address Address
		* \param data Data
		*/
		void set32bitData(uint32_t address, uint32_t data);
	private:		
		Segment &segment(uint32_t address);
		const Segment &segment(uint32_t address) const;
	};
}

#endif

#ifndef _address_space_h_
#define _address_space_h_
#include "Segment.h"
#include <map>
#include "SectionData.h"
#include "InstructionBitField.h"
#include "SymbolData.h"
#include <unordered_map>
#include <queue>

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
		 * \brief Gets the second word of the instruction at the specified address
		 * \param address Address
		 * \return Second word of the instruction
		 */
		int32_t getSecondWordOfInstruction(uint32_t address) const;

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

		/**
		 * \brief Gets the initial value of the stack pointer
		 * \return Initial value of the stack pointer
		 * \throw Throws if the initial value of the stack pointer is not defined
		 */
		uint32_t initialStackPointer() const;

		/**
		 * \brief Gets the entry of the error interrupt routine
		 * \return Entry of the error interrupt routine
		 */
		size_t errorInterrupt() const noexcept;

		/**
		* \brief Gets the entry of the timer interrupt routine
		* \return Entry of the timer interrupt routine
		*/
		size_t timerInterrupt() const noexcept;

		/**
		* \brief Gets the entry of the keyboard interrupt routine
		* \return Entry of the keyboard interrupt routine
		*/
		size_t keyboardInterrupt() const noexcept;

		/**
		 * \brief Gets the address of the interrupt routine at the specified entry
		 * \param entry Entry
		 * \return Address of the interrupt routine
		 */
		uint32_t getInterrupt(uint32_t entry) const noexcept;

		/**
		 * \brief Check whether the standard input has been read
		 * \return Whether the standard input has been read
		 */
		bool stdinRead() const noexcept;

		/**
		 * \brief Writes a character to stdin
		 */
		void writeToStdin(char character) noexcept;
	private:		
		Segment &segment(uint32_t address);
		const Segment &segment(uint32_t address) const;

		uint32_t stdout_address_ = 128;
		uint32_t stdin_address_ = 132;

		size_t error_interrupt_ = 3;
		size_t timer_interrupt_ = 4;
		size_t keyboard_interrupt_ = 5;

		mutable bool stdin_read_ = true;
	};
}

#endif

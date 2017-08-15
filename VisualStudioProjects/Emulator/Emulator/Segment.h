#ifndef _segment_h_
#define _segment_h_
#include "SectionType.h"
#include <cstdint>
#include <vector>
#include "InstructionBitField.h"

namespace bnssemulator {
	
	class Segment : std::vector<uint8_t> {
	public:
		/**
		 * \brief Constructs a segment
		 * \param address Starting address of the segment
		 * \param length Length of the segment
		 * \param type Type of the segment
		 */
		Segment(uint32_t address, size_t length, SectionType type, vector<uint8_t> &&data);

		/**
		 * \brief Gets the instruction at the specified address
		 * \param address Address
		 * \return Instruction
		 */
		InstructionBitField getInstruction(uint32_t address) const;
		
		/**
		 * \brief Reads a byte of data at the specified address
		 * \param address Address
		 * \return Byte of read data
		 */
		uint8_t readData(uint32_t address) const;

		/**
		 * \brief Writes a byte of data at the specified address
		 * \param address Address
		 * \param data Byte of data to be written
		 */
		void writeData(uint32_t address, uint8_t data);

		using vector::push_back;
		using vector::resize;
	private:
		uint32_t address_;
		size_t length_;
		SectionType type_;
	};
}

#endif

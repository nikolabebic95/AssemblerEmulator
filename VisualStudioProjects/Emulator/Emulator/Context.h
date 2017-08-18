#ifndef _context_h_
#define _context_h_
#include "Register.h"
#include <vector>
#include "AssemblerOutput.h"
#include "AddressSpace.h"
#include <queue>
#include <mutex>

namespace bnssemulator {
	
	/**
	 * \brief Class representing the context of the processor
	 */
	class Context {
	public:
		/**
		 * \brief Constructs a Context object
		 * \param assembler_output R-value reference to the assembler output object
		 * \throw Throws if the context can not be constructed
		 */
		explicit Context(AssemblerOutput &&assembler_output);
		
		/**
		 * \brief Pushes a value to the stack
		 * \param value Value to be pushed
		 * \throw Throws if stack overflow happens
		 */
		void pushToStack(int32_t value);

		/**
		 * \brief Pops a value from the stack
		 * \return Popped value
		 * \throw Throws if stack underflow happens
		 */
		int32_t popFromStack();

		/**
		 * \brief Gets the reference to the register
		 * \param index Index of the register
		 * \return Reference to the register
		 */
		Register &getRegister(size_t index) noexcept;

		/**
		* \brief Gets the reference to the register
		* \param index Index of the register
		* \return Reference to the register
		*/
		const Register &getRegister(size_t index) const noexcept;

		/**
		 * \brief Gets the address space
		 * \return Address space
		 */
		AddressSpace &addressSpace() noexcept;
		
		/**
		* \brief Gets the address space
		* \return Address space
		*/
		const AddressSpace &addressSpace() const noexcept;

		/**
		 * \brief Jumps to address
		 * \param address Address
		 */
		void jumpTo(uint32_t address);

		/**
		 * \brief Jumps to subroutine at address
		 * \param address Address
		 */
		void jumpToSubroutine(uint32_t address);

		/**
		 * \brief Jumps to interrupt routine at the specified entry
		 * \param entry Entry
		 */
		void jumpToInterrupt(size_t entry);

		/**
		 * \brief Returns from subroutine
		 */
		void returnFromSubroutine();

		/**
		 * \brief Gets the operand based on the instruction
		 * \param instruction Instruction
		 * \param register_index Index of the register to use in case of register address modes
		 * \param num_of_bytes Number of bytes of the operand
		 * \return Operand
		 */
		int32_t getOperand(InstructionBitField instruction, size_t register_index, size_t num_of_bytes = 4);

		/**
		* \brief Gets the address of the operand based on the instruction
		* \param instruction Instruction
		* \param register_index Index of the register to use in case of register address modes
		* \return Address of the operand
		*/
		int32_t getOperandAddress(InstructionBitField instruction, size_t register_index);

		/**
		 * \brief Gets the instruction to execute
		 * \return Instruction
		 */
		InstructionBitField getInstruction();

		/**
		 * \brief Gets the second word of the instruction
		 * \return Second word of the instruction
		 */
		int32_t getSecondWordOfInstruction();

		/**
		 * \brief Finishes the program
		 */
		void finishProgram() noexcept;

		/**
		 * \brief Checks whether the program finished
		 * \return Whether the program finished
		 */
		bool programFinished() const noexcept;

		/**
		 * \brief Checks whether the program is executing an interrupt routine
		 * \return Whether the program is executing an interrupt routine
		 */
		bool insideInterrupt() const noexcept;

		/**
		 * \brief Presses a character
		 * \param character Character
		 */
		void pressCharacter(char character) noexcept;
	private:
		AddressSpace address_space_;
		std::vector<Register> registers_;
		Register &stack_pointer_;
		Register &program_counter_;

		bool inside_interrupt_ = false;
		size_t interrupt_call_stack_depth_ = 0;

		std::mutex characters_mutex;
		std::queue<char> characters_;

		bool end_of_program_ = false;
	};
}

#endif

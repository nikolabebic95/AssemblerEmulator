#include "Context.h"
#include "MessageException.h"
#include "StringHelper.h"
#include "AddressMode.h"

namespace bnssemulator {

	Context::Context(AssemblerOutput && assembler_output) : address_space_(move(assembler_output.sectionTable()), assembler_output.symbolTable()), registers_(18), stack_pointer_(registers_[16]), program_counter_(registers_[17]) {
		if (assembler_output.importedSymbolsExist()) {
			throw MessageException("Can not resolve imported symbols: " + StringHelper::join(assembler_output.importedSymbolsAsVector(), ", "));
		}

		stack_pointer_.value(address_space_.initialStackPointer());
		program_counter_.value(assembler_output.startOfProgram("_start"));
	}

	void Context::pushToStack(int32_t value) {
		stack_pointer_ += 4;
		address_space_.set32bitData(stack_pointer_, value);
	}

	// ReSharper disable once CppMemberFunctionMayBeConst
	int32_t Context::popFromStack() {
		int32_t ret = address_space_.get32bitData(stack_pointer_);
		stack_pointer_ -= 4;
		return ret;
	}

	Register & Context::getRegister(size_t index) noexcept {
		return registers_[index];
	}

	const Register & Context::getRegister(size_t index) const noexcept {
		return const_cast<Context &>(*this).getRegister(index);
	}

	AddressSpace & Context::addressSpace() noexcept {
		return address_space_;
	}

	const AddressSpace & Context::addressSpace() const noexcept {
		return const_cast<Context &>(*this).addressSpace();
	}

	// ReSharper disable once CppMemberFunctionMayBeConst
	void Context::jumpTo(uint32_t address) {
		program_counter_ = address;
	}

	void Context::jumpToSubroutine(uint32_t address) {
		if (inside_interrupt_) {
			interrupt_call_stack_depth_++;
		}

		pushToStack(program_counter_);
		jumpTo(address);
	}

	void Context::jumpToInterrupt(size_t entry) {
		inside_interrupt_ = true;
		jumpToSubroutine(address_space_.getInterrupt(entry));
	}

	void Context::returnFromSubroutine() {
		if (inside_interrupt_) {
			interrupt_call_stack_depth_--;
			if (interrupt_call_stack_depth_ == 0) {
				inside_interrupt_ = false;
			}
		}

		program_counter_ = popFromStack();
	}

	/**
	 * \brief Gets the index of the register in the array of registers
	 * \param instruction Instruction
	 * \param register_index Index of the register in the instruction
	 * \return Index of the register in the array
	 */
	static size_t getRegisterIndex(InstructionBitField instruction, size_t register_index) { 
		switch (register_index) {
		case 0:
			return instruction.register0;
		case 1:
			return instruction.register1;
		case 2:
			return instruction.register2;
		default:
			throw MessageException("Invalid register index: " + StringHelper::numberFormat(register_index));
		}
	}

	int32_t Context::getOperand(InstructionBitField instruction, size_t register_index, size_t num_of_bytes) {
		int32_t val;
		switch (instruction.address_mode) {
		case IMMEDIATE:
			val = getSecondWordOfInstruction();
			return val;
		case REGISTER_DIRECT:
			return registers_[getRegisterIndex(instruction, register_index)];
		case MEMORY_DIRECT:
		case REGISTER_INDIRECT:
		case REGISTER_INDIRECT_OFFSET:
			val = getOperandAddress(instruction, register_index);
			switch (num_of_bytes) {
			case 1:
				return address_space_.get8bitData(val);
			case 2:
				return address_space_.get16bitData(val);
			case 4:
				return address_space_.get32bitData(val);
			default: 
				throw MessageException("Invalid number of bytes");
			}
		default:
			throw MessageException("Invalid address mode: " + StringHelper::toHexString(instruction.address_mode));
		}
	}

	int32_t Context::getOperandAddress(InstructionBitField instruction, size_t register_index) {
		switch (instruction.address_mode) {
		case MEMORY_DIRECT:
			return getSecondWordOfInstruction();
		case REGISTER_INDIRECT:
			return registers_[getRegisterIndex(instruction, register_index)];
		case REGISTER_INDIRECT_OFFSET:
			return static_cast<uint32_t>(registers_[getRegisterIndex(instruction, register_index)]) + getSecondWordOfInstruction();
		default:
			throw MessageException("Invalid address mode: " + StringHelper::toHexString(instruction.address_mode));
		}
	}

	// ReSharper disable once CppMemberFunctionMayBeConst
	InstructionBitField Context::getInstruction() {
		auto ret = address_space_.getInstruction(program_counter_);
		program_counter_ += 4;
		return ret;
	}

	// ReSharper disable once CppMemberFunctionMayBeConst
	int32_t Context::getSecondWordOfInstruction() {
		auto ret = address_space_.getSecondWordOfInstruction(program_counter_);
		program_counter_ += 4;
		return ret;
	}

	void Context::finishProgram() noexcept {
		end_of_program_ = true;
	}

	bool Context::programFinished() const noexcept {
		return end_of_program_;
	}

	bool Context::insideInterrupt() const noexcept {
		return inside_interrupt_;
	}

	void Context::pressCharacter(char character) noexcept {
		characters_mutex.lock();
		characters_.push(character);
		characters_mutex.unlock();
	}
}

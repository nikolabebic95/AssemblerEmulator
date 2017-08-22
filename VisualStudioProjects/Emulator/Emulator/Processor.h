#ifndef _processor_h_
#define _processor_h_
#include "Executer.h"
#include "InstructionCode.h"
#include <unordered_map>
#include <memory>

namespace bnssemulator {
	
	/**
	 * \brief Class representing the processor
	 */
	class Processor final {
	public:
		/**
		 * \brief Executes the program using the given processor context
		 * \param context Reference to the processor context
		 */
		static void executeProgram(Context &context);
	private:
		/**
		 * \brief Executes one instruction of the program using the given processor context
		 * \param context Reference to the processor context
		 */
		static void executeInstruction(Context &context);

		struct ProcessorStaticData {
			std::unordered_map<InstructionCode, std::shared_ptr<Executer>> map;
			ProcessorStaticData();
		};

		static ProcessorStaticData &staticData() noexcept;
	};
}

#endif

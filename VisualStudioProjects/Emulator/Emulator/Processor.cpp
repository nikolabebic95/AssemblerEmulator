#include "Processor.h"
#include "IntExecuter.h"
#include "RetExecuter.h"
#include "JmpExecuter.h"
#include "CallExecuter.h"
#include "JzExecuter.h"
#include "JnzExecuter.h"
#include "JgzExecuter.h"
#include "JgezExecuter.h"
#include "JlzExecuter.h"
#include "JlezExecuter.h"
#include "LoadExecuter.h"
#include "StoreExecuter.h"
#include "PushExecuter.h"
#include "PopExecuter.h"
#include "AddExecuter.h"
#include "SubtractExecuter.h"
#include "MultiplyExecuter.h"
#include "DivideExecuter.h"
#include "ModuloExecuter.h"
#include "AndExecuter.h"
#include "OrExecuter.h"
#include "XorExecuter.h"
#include "AslExecuter.h"
#include "AsrExecuter.h"
#include "NotExecuter.h"
#include "MessageException.h"
#include "StringHelper.h"
#include "KeyboardListener.h"
#include <thread>
#include "TimerListener.h"

namespace bnssemulator {

	void Processor::executeProgram(Context & context) {
		std::thread keyboard_listener(KeyboardListener::listen, &context);
		std::thread timer_thread(TimerListener::listen, &context);

		try {
			while (!context.programFinished()) {
				executeInstruction(context);

				if (context.hasCharacters() && !context.insideInterrupt()) {
					context.jumpToKeyboardInterrupt();
				}

				if (context.timerTriggered() && !context.insideInterrupt()) {
					context.jumpToTimerInterrupt();
				}
			}
		}
		catch (...) {
			context.finishProgram();
			keyboard_listener.join();
			timer_thread.join();
			throw;
		}

		keyboard_listener.join();
		timer_thread.join();
	}

	static InstructionCode opcode(InstructionBitField instruction) {
		return static_cast<InstructionCode>(instruction.operation_code);
	}

	void Processor::executeInstruction(Context &context) {
		auto instruction = context.getInstruction();
		if (staticData().map.count(opcode(instruction)) == 0) {
			throw MessageException("Invalid operation code: " + StringHelper::toHexString(instruction.operation_code));
		}

		auto &executer = staticData().map.at(opcode(instruction));
		executer->execute(instruction, context);
	}

	Processor::ProcessorStaticData::ProcessorStaticData() {
		map[INT] = std::make_shared<IntExecuter>();
		map[RET] = std::make_shared<RetExecuter>();
		map[JMP] = std::make_shared<JmpExecuter>();
		map[CALL] = std::make_shared<CallExecuter>();
		map[JZ] = std::make_shared<JzExecuter>();
		map[JNZ] = std::make_shared<JnzExecuter>();
		map[JGZ] = std::make_shared<JgzExecuter>();
		map[JGEZ] = std::make_shared<JgezExecuter>();
		map[JLZ] = std::make_shared<JlzExecuter>();
		map[JLEZ] = std::make_shared<JlezExecuter>();
		map[LOAD] = std::make_shared<LoadExecuter>();
		map[STORE] = std::make_shared<StoreExecuter>();
		map[PUSH] = std::make_shared<PushExecuter>();
		map[POP] = std::make_shared<PopExecuter>();
		map[ADD] = std::make_shared<AddExecuter>();
		map[SUB] = std::make_shared<SubtractExecuter>();
		map[MUL] = std::make_shared<MultiplyExecuter>();
		map[DIV] = std::make_shared<DivideExecuter>();
		map[MOD] = std::make_shared<ModuloExecuter>();
		map[AND] = std::make_shared<AndExecuter>();
		map[OR] = std::make_shared<OrExecuter>();
		map[XOR] = std::make_shared<XorExecuter>();
		map[ASL] = std::make_shared<AslExecuter>();
		map[ASR] = std::make_shared<AsrExecuter>();
		map[NOT] = std::make_shared<NotExecuter>();
	}

	Processor::ProcessorStaticData & Processor::staticData() noexcept {
		static ProcessorStaticData static_data;
		return static_data;
	}
}

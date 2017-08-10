#include "Data.h"

namespace bnssassembler {

	Data::Data(DataType type, MicroRiscExpression value, MicroRiscExpression count) noexcept : type_(type), value_(value), count_(count) {}

	Data::Data(DataType type, MicroRiscExpression count) noexcept : type_(type), initialized_(false), value_(nullptr), count_(count) {}

	DataType Data::type() const noexcept {
		return type_;
	}

	bool Data::initialized() const noexcept {
		return initialized_;
	}

	MicroRiscExpression Data::value() const noexcept {
		return value_;
	}

	MicroRiscExpression Data::count() const noexcept {
		return count_;
	}
}

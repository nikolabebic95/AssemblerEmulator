#include "Register.h"

namespace bnssemulator {

	static const uint64_t TOP_32_BITS = ~static_cast<uint64_t>(0) << 32;

	int32_t Register::value() const noexcept {
		return value_;
	}

	void Register::value(int32_t value) noexcept {
		value_ = value;
	}

	bool Register::negativeFlag() const noexcept {
		return value_ < 0;
	}

	bool Register::zeroFlag() const noexcept {
		return value_ == 0;
	}

	bool Register::carryFlag() const noexcept {
		return carry_flag_;
	}

	bool Register::overflowFlag() const noexcept {
		return overflow_flag_;
	}

	Register::Register(int32_t value) noexcept : value_(value) {}

	Register::operator int32_t() const noexcept {
		return value_;
	}

	Register::Register(int32_t value, bool carryFlag, bool overflowFlag) noexcept : value_(value), carry_flag_(carryFlag), overflow_flag_(overflowFlag) {}

	Register Register::operator-() const noexcept {
		return Register(-value_);
	}

	Register Register::operator~() const noexcept {
		return Register(~value_);
	}

	Register & Register::operator+=(const Register &reg) noexcept {
		*this = *this + reg;
		return *this;
	}

	Register & Register::operator-=(const Register &reg) noexcept {
		*this = *this - reg;
		return *this;
	}

	Register & Register::operator*=(const Register &reg) noexcept {
		*this = *this * reg;
		return *this;
	}

	Register & Register::operator/=(const Register &reg) noexcept {
		*this = *this / reg;
		return *this;
	}

	Register & Register::operator%=(const Register &reg) noexcept {
		*this = *this % reg;
		return *this;
	}

	Register & Register::operator&=(const Register &reg) noexcept {
		*this = *this & reg;
		return *this;
	}

	Register & Register::operator|=(const Register &reg) noexcept {
		*this = *this | reg;
		return *this;
	}

	Register & Register::operator^=(const Register &reg) noexcept {
		*this = *this ^ reg;
		return *this;
	}

	Register & Register::operator<<=(const Register &reg) noexcept {
		*this = *this << reg;
		return *this;
	}

	Register & Register::operator>>=(const Register &reg) noexcept {
		*this = *this >> reg;
		return *this;
	}

	Register operator+(const Register &lhs, const Register &rhs) noexcept {
		auto result_value = static_cast<int64_t>(lhs.value_) + static_cast<int64_t>(rhs.value_);
		auto left = static_cast<bool>(lhs.value_ & INT32_MIN);
		auto right = static_cast<bool>(rhs.value_ & INT32_MIN);
		auto result = static_cast<bool>(result_value & INT32_MIN);

		auto flags = (left && right && !result) || (!left && !right && result);
		
		return Register(static_cast<int32_t>(result_value), flags, flags);
	}

	Register operator-(const Register &lhs, const Register &rhs) noexcept {
		return lhs + -rhs;
	}

	Register operator*(const Register &lhs, const Register &rhs) noexcept {
		auto result_value = static_cast<int64_t>(lhs.value_) + static_cast<int64_t>(rhs.value_);
		auto left = static_cast<bool>(lhs.value_ & INT32_MIN);
		auto right = static_cast<bool>(rhs.value_ & INT32_MIN);
		auto result = static_cast<bool>(result_value & INT32_MIN);

		auto flags = ((result_value & TOP_32_BITS) != 0) || (!left && !right && result);

		return Register(static_cast<int32_t>(result_value), flags, flags);
	}

	Register operator/(const Register &lhs, const Register &rhs) noexcept {
		return Register(lhs.value_ / rhs.value_);
	}

	Register operator%(const Register &lhs, const Register &rhs) noexcept {
		return Register(lhs.value_ % rhs.value_);
	}

	Register operator&(const Register &lhs, const Register &rhs) noexcept {
		return Register(lhs.value_ & rhs.value_);
	}

	Register operator|(const Register &lhs, const Register &rhs) noexcept {
		return Register(lhs.value_ | rhs.value_);
	}

	Register operator^(const Register &lhs, const Register &rhs) noexcept {
		return Register(lhs.value_ ^ rhs.value_);
	}

	Register operator<<(const Register &lhs, const Register &rhs) noexcept {
		auto shift = rhs.value_ % 32;
		auto result = lhs.value_ << shift;

		auto carry = (result & TOP_32_BITS) != 0;

		return Register(result, carry, false);
	}

	Register operator>>(const Register &lhs, const Register &rhs) noexcept {
		auto shift = rhs.value_ % 32;
		auto result = lhs.value_ >> shift;

		auto back = result << shift;
		auto carry = lhs.value_ != back;

		return Register(result, carry, false);
	}
}

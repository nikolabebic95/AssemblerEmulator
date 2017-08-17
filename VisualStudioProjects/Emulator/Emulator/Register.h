#ifndef _register_h_
#define _register_h_
#include <cstdint>

namespace bnssemulator {
	
	/**
	 * \brief Class representing the register
	 */
	class Register {
	public:
		Register() = default;

		int32_t value() const noexcept;
		void value(int32_t value) noexcept;

		bool negativeFlag() const noexcept;
		bool zeroFlag() const noexcept;
		bool carryFlag() const noexcept;
		bool overflowFlag() const noexcept;

		// ReSharper disable once CppNonExplicitConvertingConstructor
		Register(int32_t value) noexcept;
		// ReSharper disable once CppNonExplicitConversionOperator
		operator int32_t() const noexcept;
		Register(int32_t value, bool carryFlag, bool overflowFlag) noexcept;

		Register operator-() const noexcept;
		Register operator~() const noexcept;

		Register &operator+=(const Register &reg) noexcept;
		Register &operator-=(const Register &reg) noexcept;
		Register &operator*=(const Register &reg) noexcept;
		Register &operator/=(const Register &reg) noexcept;
		Register &operator%=(const Register &reg) noexcept;

		Register &operator&=(const Register &reg) noexcept;
		Register &operator|=(const Register &reg) noexcept;
		Register &operator^=(const Register &reg) noexcept;

		Register &operator<<=(const Register &reg) noexcept;
		Register &operator>>=(const Register &reg) noexcept;

		friend Register operator+(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator-(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator*(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator/(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator%(const Register &lhs, const Register &rhs) noexcept;

		friend Register operator&(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator|(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator^(const Register &lhs, const Register &rhs) noexcept;		

		friend Register operator<<(const Register &lhs, const Register &rhs) noexcept;
		friend Register operator>>(const Register &lhs, const Register &rhs) noexcept;
	private:
		int32_t value_ = 0;

		bool carry_flag_ = false;
		bool overflow_flag_ = false;
	};
}

#endif

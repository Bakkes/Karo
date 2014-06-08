#pragma once

#include <gmp.h>
#include "DllImportExport.h"

namespace engine {
	class ENGINE_API BigInteger {

	public:
		BigInteger();
		BigInteger(unsigned int val);
		BigInteger(const BigInteger& instance);
		~BigInteger();

		void multiply(BigInteger integer);
		void multiply2exp(int integer);

		void set(int integer);

		BigInteger& operator = (const BigInteger& instance);

		friend BigInteger operator ^ (const BigInteger& lhs, const BigInteger& rhs) {
			BigInteger c(lhs);
			mpz_xor(c._value, c._value, rhs._value);
			return c;
		}

		friend BigInteger& operator ^= (BigInteger& lhs, const BigInteger& instance) {
			mpz_xor(lhs._value, lhs._value, instance._value);
			return lhs;
		}

		friend bool operator == (const BigInteger& lhs, const BigInteger& rhs) {
			BigInteger c(lhs);
			mpz_sub(c._value, c._value, rhs._value);
			return mpz_sgn(c._value) == 0;
		}

		friend bool operator != (const BigInteger& lhs, const BigInteger& rhs) {
			return !(lhs == rhs);
		}

		friend bool operator < (const BigInteger& lhs, const BigInteger& rhs) {
			BigInteger c(lhs);
			mpz_sub(c._value, c._value, rhs._value);
			return mpz_sgn(c._value) < 0;
		}

		friend bool operator > (const BigInteger& lhs, const BigInteger& rhs) {
			BigInteger c(lhs);
			mpz_sub(c._value, c._value, rhs._value);
			return mpz_sgn(c._value) > 0;
		}

		friend bool operator <= (const BigInteger& lhs, const BigInteger& rhs) {
			BigInteger c(lhs);
			mpz_sub(c._value, c._value, rhs._value);
			return mpz_sgn(c._value) <= 0;
		}

		friend bool operator >= (const BigInteger& lhs, const BigInteger& rhs) {
			BigInteger c(lhs);
			mpz_sub(c._value, c._value, rhs._value);
			return mpz_sgn(c._value) >= 0;
		}

	private:
		mpz_t _value;
	};
}


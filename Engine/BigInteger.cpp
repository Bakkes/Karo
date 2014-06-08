#include "BigInteger.h"

namespace engine {

	BigInteger::BigInteger() {
		mpz_init(_value);
	}

	BigInteger::BigInteger(unsigned int val) {
		mpz_init(_value);
		set(val);
	}

	BigInteger::BigInteger(const BigInteger& instance) {
		mpz_init(_value);
		mpz_add(_value, _value, instance._value);
	}

	BigInteger::~BigInteger() {
		mpz_clear(_value);
	}

	void BigInteger::set(int integer) {
		mpz_set_ui(_value, integer);
	}

	void BigInteger::set(char* string, int base) {
		mpz_set_str(_value, string, base);
	}

	void BigInteger::multiply(BigInteger integer) {
		mpz_mul(_value, _value, integer._value);
	}

	void BigInteger::multiply2exp(int exponent) {
		mpz_mul_2exp(_value, _value, exponent);
	}

	BigInteger& BigInteger::operator = (const BigInteger& instance) {
		mpz_set(_value, instance._value);
		return *this;
	}
}

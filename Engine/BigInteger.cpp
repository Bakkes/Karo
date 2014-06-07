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
		mpz_set(_value, instance._value);
	}

	BigInteger::~BigInteger() {
		mpz_clear(_value);
	}

	void BigInteger::set(int integer) {
		mpz_set_ui(_value, integer);
	}

	void BigInteger::multiply(BigInteger integer) {
		mpz_mul(_value, _value, integer._value);
	}

	void BigInteger::multiply2exp(int exponent) {
		mpz_mul_2exp(_value, _value, exponent);
		gmp_printf("%Zd\n", _value);
	}

	BigInteger& BigInteger::operator = (BigInteger instance) {
		mpz_set(_value, instance._value);
		return *this;
	}

	BigInteger& BigInteger::operator ^ (BigInteger instance) {
		mpz_xor(_value, _value, instance._value);
		return *this;
	}
}

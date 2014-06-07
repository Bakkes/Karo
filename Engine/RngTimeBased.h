#pragma once
#include <list>
#include <random>
#include "IRng.h"

namespace engine { 

	class ENGINE_API RngTimeBased : public IRng {

	public:
		RngTimeBased();
		virtual ~RngTimeBased();

		long long NextInteger() override;

	private:
		long long CreateLong();

		std::list<long long>* _returnedNumbers;
		std::mt19937_64* _mersenne;

	};

}
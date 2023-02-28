#pragma once 
#include <cstdint>
#include <stdio.h>
#include <random>
namespace Skele_lib {
	namespace SKGE {
		class RNG {
			static void Warn() {
				printf(" this is an old API use ./headers/random.h instead"); 
			}
			static const uint32_t M_RAND = 1 << 31;
			std::random_device rd; // obtain a random number from hardware
		public:
			double GetNextNumberAsPercent(int min = 0, int max = 100) {
				Warn(); 
				return (double)this->operator()(min, max) / (double)max;
			}

			template <typename T> T operator()(T min, T max) {
				std::uniform_int_distribution<T> distr(min, max); // define the range
				std::mt19937 gen(rd()); // seed the generator
				Warn();
				return distr(gen);
			}
			template <typename T> T operator()() {
				Warn(); 
				std::uniform_int_distribution<T> distr(0, M_RAND); // define the range
				std::mt19937 gen(rd()); // seed the generator
				return distr(gen);
			}
		};
	}
}
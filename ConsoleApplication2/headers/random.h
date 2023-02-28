#pragma once
#include <random>
#include <vector>
namespace Skele_lib {
	namespace SKGE {
		namespace RNG {
			typedef unsigned char uint8_t;

			class MersenneTwister {
				std::mt19937 generator;
			public:
				explicit MersenneTwister(unsigned seed) {
					generator = std::mt19937(seed);
				}
				MersenneTwister() {
					generator = std::mt19937((std::random_device{})());
				}
				auto operator()() {
					return generator();
				}
				std::vector<size_t> GetNNext(int n) {
					std::vector<size_t> numbers;
					for (size_t i = 0; i < n; i++)
					{
						numbers.push_back(generator());
					}
					return numbers;
				}
				size_t Next() {
					return this->operator()(); 
				}
				size_t GetInRange(size_t min, size_t max) {
					auto range = max - min; 
					return min + ((double)(generator()) / (double)std::mt19937::max()) * range; 
				}
				
				void GetNextColor(uint8_t& r, uint8_t& g, uint8_t& b) {
					auto color = Next();
					//0x00ffaaff
					//g = (uint8_t)(color & 0x0000ff) >> 0;
					//b = (uint8_t)(color & 0x0000ff) >> 0;
					b = (color & 0x0000ff) >> 0;
					g = (color & 0x00ff00) >> 8;
					r = (color & 0xff0000) >> 16;
					//std::cout << std::format("color {}, r:{} g:{} b:{}\r",color, (Next() & 0x0000ff) >> 0, (Next() & 0x00ff00) >> 8, (Next() & 0xff0000) >> 16);
				};
			};
			typedef MersenneTwister sMT;
		}
	}
}
#pragma once
#include <chrono>
#include <thread>
namespace Skele_lib {
	namespace SKGE {
		namespace Timer {
			typedef std::chrono::time_point<std::chrono::system_clock> chrono_sysclock_t;
			typedef std::chrono::milliseconds chrono_ms_t;
			typedef unsigned long long frameCount_t;
			typedef long double ElapsedTime_t; 
			auto Wait(const chrono_sysclock_t &tp1, const chrono_sysclock_t &tp2, chrono_ms_t frameTime, ElapsedTime_T & fElapsedTime) {
				std::chrono::duration<float> difference = tp2 - tp1;
				std::this_thread::sleep_for(frameTime - difference);
				fElapsedTime = (long double)frameTime.count() / 1000;
				return difference;
			}
		}
	}
}
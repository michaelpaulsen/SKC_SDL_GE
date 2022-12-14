#pragma once
#include "./EventHandler.h"
#include <SDL.h>
namespace Skele_lib {
	namespace SKGE {
		struct GameState {
			Timer::frameCount_t frame; 
			Timer::ElapsedTime_T fElapsedTime;
			int TFPS; 
			
			GameState(int tfs) {
				TFPS = tfs; 
				frame = 0;
				fElapsedTime = 0; 
			}
			Timer::chrono_ms_t GetFrameTime() {
				return Timer::chrono_ms_t(1000 / TFPS);
			}
		};
	}
}
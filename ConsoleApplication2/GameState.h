#pragma once
#include "./EventHandler.h"
#include <SDL.h>
namespace Skele_lib {
	namespace SKGE {
		struct World {
			unsigned long long frame;
			long double fElapsedTime;
			int TFPS; 
			
			World(int tfs) {
				TFPS = tfs; 
				frame = 0;
				fElapsedTime = 0; 
			}
			std::chrono::milliseconds GetFrameTime() {
				return std::chrono::milliseconds(1000 / TFPS);
			}
		};
	}
}
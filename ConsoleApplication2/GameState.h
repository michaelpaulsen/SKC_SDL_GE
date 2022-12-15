#pragma once
#include "./EventHandler.h"
#include <vector>
#include <SDL.h>
#include "./Player.h"
namespace Skele_lib {
	namespace SKGE {
		struct World{
			unsigned long long frame;
			long double fElapsedTime;
			int TFPS; 
			std::vector<Player> playerQue; 
			size_t players;
			World(int tfs) {
				TFPS = tfs; 
				frame = 0;
				fElapsedTime = 0;
				players = 0; 
			}
			std::chrono::milliseconds GetFrameTime() {
				return std::chrono::milliseconds(1000 / TFPS);
			}
			void AddPlayer(const char* path, SDL_Renderer* renderer, vec2d _s, vec2d _p = { 0,0 }) {
				playerQue.emplace_back(path, renderer, _s, _p);
				players++; 
			}
			Player& GetPlayerAt(size_t index) {
				return playerQue.at(index);
			}
		};
	}
}
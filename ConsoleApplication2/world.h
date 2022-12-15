#pragma once
#pragma once
#include <vector>
#include <SDL.h>
#include <chrono>
#include "./Player.h"
#include "./Window.h"
#include "./sprite.h"
namespace Skele_lib {
	namespace SKGE {
		class World {
			typedef unsigned long long FrameN_t;
			FrameN_t frame;
			FrameN_t TFPS;
			size_t players;
		public:
			std::vector<Player> playerQue;

			long double fElapsedTime;
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
			FrameN_t GetFrame() {
				return frame;
			}
			void IncFrame() {
				++frame;
			}
			void SetTargetFPS(FrameN_t targetFPS) {
				TFPS = targetFPS;
			}
		};
	}
}
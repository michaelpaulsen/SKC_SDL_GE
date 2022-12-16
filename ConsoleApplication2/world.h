#pragma once
#pragma once
#include <vector>
#include <SDL.h>
#include <chrono>
#include "./Player.h"
#include "./Window.h"
#include "./sprite.h"
#ifndef MAX_PLAYERS
#define MAX_PLAYERS 4 
#endif // !MAX_PLAYERS
namespace Skele_lib {
	namespace SKGE {
		class World {
			typedef unsigned long long FrameN_t;
			FrameN_t frame;
			FrameN_t TFPS;
			size_t m_players;
			Player* l_players;
		public:
			long double fElapsedTime;
			World(int tfs) {
				TFPS = tfs;
				frame = 0;
				fElapsedTime = 0;
				m_players = 0;
				l_players = (Player*)malloc(sizeof(Player)*MAX_PLAYERS); 
			}
			std::chrono::milliseconds GetFrameTime() {
				return std::chrono::milliseconds(1000 / TFPS);
			}
			void AddPlayer(const char* path, SDL_Renderer* renderer, double _sx, double _sy, double _px, double _py) {
				if (m_players != MAX_PLAYERS) {
					l_players[m_players] = Player(path, renderer, _sx, _sy, _px, _py);
					m_players++;

				}
			}
			Player& GetPlayerAt(size_t index) {
				if (index > m_players) {
					return  l_players[m_players]; 
				}
				return l_players[index]; 

			}
			void DrawPlayers(SDL_Renderer* r) {
				for (size_t i = 0; i < m_players; i++)
				{
					auto rect = l_players[i].getPlayerRect(); 
					l_players[i].DrawSprite(r);
				}
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
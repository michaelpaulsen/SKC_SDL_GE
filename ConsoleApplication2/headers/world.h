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
			void AddPlayer(const char* path, SDL_Renderer* renderer, double _sx, double _sy, double _px, double _py, double _dx =1, double _dy =1) {
				if (m_players != MAX_PLAYERS) {
					l_players[m_players] = Player(path, renderer, _sx, _sy, _px, _py, _dx, _dy);
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
				for (size_t i = 0; i < m_players; i++){
					l_players[i].DrawSprite(r);
				}
			}
			void ApplyForceToPlayers(int w, int h) {
				for (size_t i = 0; i < m_players; i++){
					double p_forceVecX, p_forceVecY; 
					auto& player = l_players[i];
					player.GetForce(p_forceVecX, p_forceVecY);
					player.ApplyForceAndSetPos();
					auto rect = player.getPlayerRect();
					if ((rect.x <= 0 && p_forceVecX < 0) || (rect.x >= w- rect.w && p_forceVecX > 0))  {
						player.BounceHorizontal(); 
					}
					if ((rect.y <= 0 && p_forceVecY < 0) || (rect.y >= h- rect.h && p_forceVecY > 0)) {
						player.BounceVirtical();
					}
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
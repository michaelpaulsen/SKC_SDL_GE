#pragma once
#include <vector>
#include <SDL.h>
#include <chrono>
#include "./Player.h"
#include "./Window.h"
#include "./Physics.h"
#include "./sprite.h"
#include "./EventHandler.h"
#ifndef MAX_PLAYERS
#define MAX_PLAYERS 4 
#endif // !MAX_PLAYERS
namespace Skele_lib {
	namespace SKGE {
		class World {
			typedef unsigned long long FrameN_t;
			FrameN_t m_frame;
			FrameN_t TFPS;
			size_t m_players;
			GameObject::Player* l_players;
		public:
			long double dElapsedTime;
			World(int tfs) {
				TFPS = tfs;
				m_frame = 0;
				dElapsedTime = 0;
				m_players = 0;
				l_players = (GameObject::Player*)malloc(sizeof(GameObject::Player)*MAX_PLAYERS);
			}
			std::chrono::milliseconds GetFrameTime                () {
				return std::chrono::milliseconds(1000 / TFPS);
			}
			GameObject::Player&                   GetPlayerAt                 (size_t index) {
				if (index > m_players) {
					return  l_players[m_players];
				}
				return l_players[index];

			}
			FrameN_t                  GetFrame                    ()        { return           m_frame; }
			size_t                    GetPlayerCount              ()    { return         m_players; }
			void                      AddPlayer                   (const char* path, SDL_Renderer* renderer, Vector::Vec2d _s, Vector::Vec2i _p, Vector::Vec2d _d) {
				if (m_players != MAX_PLAYERS) {
					l_players[m_players] = GameObject::Player(path, renderer, _s, _p,_d);
					m_players++;

				}
			}
			void                      DrawPlayers                 (SDL_Renderer* r) {
				for (size_t i = 0; i < m_players; i++){
					l_players[i].DrawSprite(r);
				}
			}
			void                      ApplyForceToPlayers         () {
				for (size_t i = 0; i < m_players; i++){
					auto& player = l_players[i];
					auto& force = player.GetForce();
					auto& pos = player.GetPosition();
					const auto& drag = player.GetDrag();
					Skele_lib::SKGE::Physics::ApplyForceAndSetPos(pos, force, drag);
				}
			}
			void                      BouncePlayersOffWorldBounds (int w, int h) {
				for (size_t i = 0; i < m_players; i++){
					auto& player = l_players[i];
					auto& force = player.GetForce();
					auto rect = player.getPlayerRect();
					if ((rect.x <= 0 && force.m_x < 0) || (rect.x >= w - rect.w && force.m_x > 0))  {
						Skele_lib::SKGE::Physics::BounceHorizontal(force);
					}
					if ((rect.y <= 0 && force.m_y < 0) || (rect.y >= h - rect.h && force.m_y > 0))  {
						Skele_lib::SKGE::Physics::BounceVirtical(force);
					}
				}
			}
			void                      IncFrame                    () {
				++m_frame;
			}
			void                      SetTargetFPS                (FrameN_t targetFPS) {
				TFPS = targetFPS;
			}
		};
	}
}
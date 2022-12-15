#pragma once
#include "sprite.h"
#include "Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		struct Player{
			Sprite m_sprite;
			vec2d m_position; 
			vec2d m_size; 
			int	m_score;
			Player(const char* path, SDL_Renderer* renderer, vec2d _s, vec2d _p = { 0,0 }) {
				vec2d rect = { _s.x,_s.y };
				m_sprite = Sprite(path, renderer, rect);
				m_position = { 0,0 }; 
				m_size = _s;
				m_score = 0; 
			}
			SDL_Rect getPlayerRect() {
				return {(int)m_position.x,(int)m_position.y,(int)m_size.x,(int)m_size.y};	
			}
		};
	}
}

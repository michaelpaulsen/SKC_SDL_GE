#pragma once
#include "sprite.h"
#include "Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		struct Player{
			Sprite m_sprite;
			vec2d m_position; 
			vec2d m_size, m_baseSize;
			int	m_score;
			Player(const char* path, SDL_Renderer* renderer, Vec2d _s, Vec2d _p) {
				Vec2d rect = { _s.m_x,_s.m_y };
				m_sprite = Sprite(path, renderer, rect);
				m_position = { 0,0 }; 
				m_size =m_baseSize = _s;
				m_score = 0; 
			}
			SDL_Rect getPlayerRect() {
				return {(int)m_position.m_x,(int)m_position.m_y,(int)m_size.m_x,(int)m_size.m_y};	
			}
			void SetUVMap(SDL_Rect uvm) {
				m_sprite.SetUVMap(uvm);
			}
			void ClearUVMap() {
				m_sprite.ClearUVMap();
			}
			void SetScale(double scale) {
				m_size *= scale;
				m_sprite.SetScale(scale); 
			}
			void ClearScale() {
				m_size = m_baseSize; //this is why we have m_baseSize 
				m_sprite.ClearScale();
			}
			void DrawSprite(SDL_Renderer* renderer) {
				m_sprite.DrawSprite(renderer, m_position);
			}
		};
	}
}

#pragma once
#include "sprite.h"
#include "Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		class Player{
			Sprite m_sprite;
			Vector::Vec2d m_position, m_baseSize;
			Vector::Vec2d m_size;
			int	m_score ;
		public:
			Player(const char* path, SDL_Renderer* renderer, Vector::Vec2d _s, Vector::Vec2d _p) {
				Vector::Vec2d vect = { _s.m_x,_s.m_y };
				m_sprite = Sprite(path, renderer, vect);
				m_position = { 0,0 }; 
				m_size =  m_baseSize = _s;
			//	m_size = (Vector::Vec2d*)malloc(sizeof(Vector::Vec2d));
			//	m_size->m_x = _s.m_x; 
			//	m_size->m_y = _s.m_y; 
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

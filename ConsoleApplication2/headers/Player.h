#pragma once
#include "sprite.h"
#include "Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		class Player{
			Sprite m_sprite;
			Vector::Vec2d m_size, m_position, m_force,m_scale,m_drag;
			int	m_score ;
		public:
			Player() {
				m_sprite = Sprite();
				m_size = { 0,0 }; 
				m_position = { 0,0 }; 
				m_force = { 0,0 }; 
				m_drag = { 0,0 };
				m_score = 0; 
			}
			Player(const char* path, SDL_Renderer* renderer, Vector::Vec2d _s, Vector::Vec2d _p, Vector::Vec2d _d) {
				m_sprite = Sprite(path, renderer,_s);
				m_position = _p; 
				m_size = _s;
				m_force = { 0,0 };
				m_drag = _d;
				m_score = 0; 
			}
			SDL_Rect getPlayerRect() {
				auto size = m_size * m_scale; 
				return {(int)m_position.m_x,(int)m_position.m_y,(int)size.m_w,(int)size.m_h};
			}
			Vector::Vec2d  GetScale() { return m_scale;}
			Vector::Vec2d& GetPosition() { return m_position;}
			Vector::Vec2d& GetDrag() { return m_drag;}
			Vector::Vec2d& GetForce() { return m_force;}
			void SetUVMap(SDL_Rect uvm) { m_sprite.SetUVMap(uvm); }
			void ClearUVMap() { m_sprite.ClearUVMap(); }
			void SetXYScale(double scale) {
				m_size = scale;
				m_sprite.SetXYScale(scale);
			}
			void ClearScale() {
				m_scale = {1,1}; //this is why we have m_baseSize 
				m_sprite.ClearScale();
			}
			void DrawSprite(SDL_Renderer* renderer) { m_sprite.DrawSprite(renderer, m_position.m_x, m_position.m_y);}
			void SetXScale(double scale) { m_sprite.SetXScale(scale); }
			void SetYScale(double scale) { m_sprite.SetYScale(scale); }
		};
	}
}

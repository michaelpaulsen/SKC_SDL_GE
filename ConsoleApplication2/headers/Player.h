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
				m_size = m_position = m_force = m_drag = { 0,0 };
				m_score = 0; 
			}
			Player(const char* path, SDL_Renderer* renderer, Vector::Vec2d _s, Vector::Vec2d _p, Vector::Vec2d _d) {
				m_sprite = Sprite(path, renderer,_s.m_x,_s.m_y);
				m_position = _p; 
				m_size = _s;
				m_force = { 0,0 };
				m_drag = _d;
				m_score = 0; 
			}
			SDL_Rect getPlayerRect() {
				return {(int)m_position.m_x,(int)m_position.m_y,(int)m_size.m_w,(int)m_size.m_h};
			}
			void BounceHorizontal() {
				m_force.m_x = -m_force.m_x; 
			}
			void BounceVirtical() {
				m_force.m_y = -m_force.m_y; 
			}
			void SetUVMap(SDL_Rect uvm) {
				m_sprite.SetUVMap(uvm);
			}
			void ClearUVMap() {
				m_sprite.ClearUVMap();
			}
			void SetXYScale(double scale) {
				m_scale = {1,1}; 
				//this is a hack we should implement a real scaling system like the one in Sprite
				// however that might be slow when comparing for non-static collision checking. 
				// so I think that this would be the best way of doing this. 
				m_size *= scale;
				m_sprite.SetXYScale(scale); 

			}
			void AddForce(Vector::Vec2d force) {
				printf("adding force (%f, %f)\n", force.m_x, force.m_y);
				m_force += force; 
			}
			void SetForce(Vector::Vec2d force) {
				m_force = force;
			}
			void ApplyForceAndSetPos() {
				if (m_force.m_x) {
					m_position.m_x += m_force.m_x;
					if (m_force.m_x > 0) m_force.m_x -= m_drag.m_x;
					if (m_force.m_x < 0) m_force.m_x += m_drag.m_x;
				}
				if (m_force.m_y) {
					m_position.m_y += m_force.m_y;
					if (m_force.m_y > 0) m_force.m_y -= m_drag.m_y;
					if (m_force.m_y < 0) m_force.m_y += m_drag.m_y;
				}
			}
			void SetDragForce(double drag) {
				m_drag.m_x = drag;
				m_drag.m_y = drag;
			}; 
			void GetScale(double& scaleX, double& scaleY) {
				scaleX = m_size.m_w;
				scaleY = m_size.m_h;
			}
			void GetForce(double& scaleX, double& scaleY) {
				scaleX = m_force.m_x;
				scaleY = m_force.m_y;
			}
			void ClearScale() {
				m_scale = {1,1}; //this is why we have m_baseSize 
				m_sprite.ClearScale();
			}
			void DrawSprite(SDL_Renderer* renderer) {
				m_sprite.DrawSprite(renderer, m_position.m_x, m_position.m_y);
			}
			void SetXScale(double scale) {
				m_sprite.SetXScale(scale); 
			}
			void SetYScale(double scale) {
				m_sprite.SetYScale(scale); 
			}
		};
	}
}

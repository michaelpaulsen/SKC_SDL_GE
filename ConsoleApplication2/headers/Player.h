#pragma once
#include "sprite.h"
#include "Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		class Player{
			Sprite m_sprite;
			double m_size_w, m_position_x, m_baseSize_x, m_force_x,m_drag_x;
			double m_size_h, m_position_y, m_baseSize_y, m_force_y,m_drag_y;
			int	m_score ;
		public:
			Player() {
				m_sprite = Sprite();
				m_size_w = m_position_x = m_baseSize_x = m_baseSize_x = m_force_x = m_drag_x = 0;
				m_size_h = m_position_y = m_baseSize_y = m_baseSize_y = m_force_y = m_drag_y = 0;
				m_score = 0; 
			}
			Player(const char* path, SDL_Renderer* renderer, double _sx, double _sy, double _px, double _py, double _dx, double _dy) {
				m_sprite = Sprite(path, renderer,_sx,_sy);
				m_position_x = _px; 
				m_position_y = _py; 
				m_size_w =  m_baseSize_x = _sx;
				m_size_h =  m_baseSize_y = _sy;
				m_force_x = m_force_y = m_score = 0;
				m_drag_x = _dx; 
				m_drag_y = _dy; 
			}
			SDL_Rect getPlayerRect() {
				return {(int)m_position_x,(int)m_position_y,(int)m_size_w,(int)m_size_h};	
			}
			void BounceHorizontal() {
				m_force_x = -m_force_x; 
			}
			void BounceVirtical() {
				m_force_y = -m_force_y; 
			}
			void SetUVMap(SDL_Rect uvm) {
				m_sprite.SetUVMap(uvm);
			}
			void ClearUVMap() {
				m_sprite.ClearUVMap();
			}
			void SetXYScale(double scale) {
				m_size_w = m_baseSize_x; //this is why we have m_baseSize 
				m_size_h = m_baseSize_y; //this is why we have m_baseSize 
				//this is a hack we should implement a real scaling system like the one in Sprite
				// however that might be slow when comparing for non-static collision checking. 
				// so I think that this would be the best way of doing this. 
				m_size_w *= scale;
				m_size_h *= scale;
				m_sprite.SetXYScale(scale); 

			}
			void AddForce(double force_x,double force_y) {
				printf("adding force (%f, %f)\n", force_x, force_y);
				m_force_x += force_x; 
				m_force_y += force_y; 
			}
			void SetForce(double x = 0, double y = 0) {
				m_force_x = x;
				m_force_y = y;
			}
			void ApplyForceAndSetPos() {
				if (m_force_x) {
					m_position_x += m_force_x;
					if (m_force_x > 0) m_force_x -= m_drag_x;
					if (m_force_x < 0) m_force_x += m_drag_x;
				}
				if (m_force_y) {
					m_position_y += m_force_y;
					if (m_force_y > 0) m_force_y -= m_drag_y;
					if (m_force_y < 0) m_force_y += m_drag_y;
				}
			}
			void SetDragForce(double drag) {
				m_drag_x = drag;
				m_drag_y = drag;
			}; 
			void GetScale(double& scaleX, double& scaleY) {
				scaleX = m_size_w;
				scaleY = m_size_h;
			}
			void GetForce(double& scaleX, double& scaleY) {
				scaleX = m_force_x;
				scaleY = m_force_y;
			}
			void ClearScale() {
				m_size_w = m_baseSize_x; //this is why we have m_baseSize 
				m_size_h = m_baseSize_y; //this is why we have m_baseSize 
				m_sprite.ClearScale();
			}
			void DrawSprite(SDL_Renderer* renderer) {
				m_sprite.DrawSprite(renderer, m_position_x, m_position_y);
			}
			void SetXScale(double scale) {
				m_sprite.SetXScale(scale); 
			}
			void SetYScale(double scale) {
				m_sprite.SetYScale(scale); 
			}
			void MoveNorth(double speed) {
			
				m_position_y--;
			}
			void MoveSouth(double speed) {
				m_position_y++;
			}
			void moveEast(double speed) {
				m_position_x++;
			}
			void MoveWest(double speed) {
				m_position_x--; 
			}
		};
	}
}

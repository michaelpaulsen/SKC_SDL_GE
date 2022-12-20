#pragma once
#include <SDL.h>
#include <math.h>
namespace Skele_lib {
	namespace SKGE {
		namespace Vector {
			struct Vec2i {
				union {
					int m_x, m_w;
				};
				union {
					int m_y, m_h;
				};

				Vec2i(int x, int y) {
					m_x = x;
					m_y = y;
				}
				Vec2i() {
					m_x = 0;
					m_y = 0;
				}
				bool IsXLess(Vec2d o) { return m_x < o.m_x; }
				bool IsYLess(Vec2d o) { return m_y < o.m_y; }
				bool IsXMore(Vec2d o) { return m_x > o.m_x; }
				bool IsYMore(Vec2d o) { return m_y > o.m_y; }
				bool IsXLess(int o) { return m_x < o; }
				bool IsYLess(int o) { return m_y < o; }
				bool IsXMore(int o) { return m_x > o; }
				bool IsYMore(int o) { return m_y > o; }
				SDL_Rect ToSDL_Rect() { return { 0,0,m_w,m_h }; }
				SDL_Rect AsOriginOfSDL_Rect(int width, int height) { return { m_x,m_y, width, height }; }
				SDL_Rect AsOriginOfSDL_Rect(Vec2i o) { return { m_x,m_y,o.m_x,o.m_y }; }
				Vec2i AbsDist(Vec2i o) { return { abs(m_x - o.m_x), abs(m_y - o.m_y) }; }
				Vec2i Dist(Vec2i o) { return { (m_x - o.m_x), (m_y - o.m_y) }; }
				static Vec2i PosFromSDL_Rect(SDL_Rect rect) { return { rect.x, rect.y }; }
				int Fleng() { return m_x * m_x + m_y * m_y; }
				Vec2i operator*(Vec2d o) {
					Vec2i temp;
					temp.m_x = m_x * o.m_x;
					temp.m_y = m_y * o.m_y;
					return temp;
				}
				Vec2i operator/(Vec2d o) {
					Vec2i temp;
					temp.m_x = m_x / o.m_x;
					temp.m_y = m_y / o.m_y;
					return temp;
				}
				Vec2i operator+(Vec2d o) {
					Vec2i temp;
					temp.m_x = m_x + o.m_x;
					temp.m_y = m_y + o.m_y;
					return temp;
				}
				Vec2i operator-(Vec2d o) {
					Vec2i temp;
					temp.m_x = m_x - o.m_x;
					temp.m_y = m_y - o.m_y;
					return temp;
				}
				Vec2i operator-(double o) {
					//this is a short hand for this - {o,o}; 
					Vec2i temp;
					temp.m_x = m_x - o;
					temp.m_y = m_y - o;
					return temp;
				}
				Vec2i operator+(double o) {
					//this is a short hand for this - {o,o}; 
					Vec2i temp;
					temp.m_x = m_x + o;
					temp.m_y = m_y + o;
					return temp;
				}
				Vec2i operator/(double i) {
					Vec2i temp;
					temp.m_x = m_x / i;
					temp.m_y = m_y / i;
					return temp;
				}
				Vec2i operator*(double i) {
					Vec2i temp;
					temp.m_x = m_x * i;
					temp.m_y = m_y * i;
					return temp;
				}
				void operator*=(Vec2i o) {
					m_x *= o.m_x;
					m_y *= o.m_y;
				}
				void operator*=(int i) {
					m_x *= i;
					m_y *= i;
				}
				void operator/=(Vec2i o) {
					m_x /= o.m_x;
					m_y /= o.m_y;
				}
				void operator/=(int i) {
					m_x /= i;
					m_y /= i;
				}
				void operator-=(Vec2i o) {
					m_x -= o.m_x;
					m_y -= o.m_y;
				}
				void operator+=(Vec2i o) {
					m_x += o.m_x;
					m_y += o.m_y;
				}
				void operator-=(int o) {
					// this is not technically a valid operation in LA but this is a short hand for
					// this - [o,o] wich is so that is why I implement it. 

					m_x -= o;
					m_y -= o;
				}
				void operator+=(int o) {
					// this is not technically a valid operation in LA but this is a short hand for
					// this + [o,o] wich is so that is why I implement it. 

					m_x += o;
					m_y += o;
				}
				void operator=(Vec2i o) {
					m_x = o.m_x;
					m_y = o.m_y;
				}
				void operator=(int o) {
					m_x = o;
					m_y = o;
				}
				bool operator==(Vec2i o) { return (m_x == o.m_x) && (m_y == o.m_x); }
				bool operator!=(Vec2i o) { return !(*this == o); }
				bool operator<(Vec2i o) { return (m_x < o.m_x) && (m_y < o.m_y); }
				bool operator>(Vec2i o) { return (m_x > o.m_x) && (m_y > o.m_y); }
			};
		}
	}
}
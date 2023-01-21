#pragma once
#include <SDL.h>
#include <math.h>
namespace Skele_lib {
	namespace SKGE {
		namespace Vector {
			template <typename T> T tabs(T number) {
				if (number < 0) {
					return -number; 
				}
				return number; 
			}
			template <typename T> struct Vec2 {
				union {
					T m_x, m_w;
				};
				union {
					T m_y, m_h;
				};
				explicit Vec2(T s) { m_x = m_y = s; }
				Vec2(T x, T y) {
					m_x = x;
					m_y = y;
				}
				Vec2() {
					m_x = 0;
					m_y = 0;
				}
				bool IsXLess(Vec2 o)  { return m_x < o.m_x;}
				bool IsYLess(Vec2 o)  { return m_y < o.m_y;}
				bool IsXMore(Vec2 o)  { return m_x > o.m_x;}
				bool IsYMore(Vec2 o)  { return m_y > o.m_y;}
				bool IsXLess(T o) { return m_x < o;}
				bool IsYLess(T o) { return m_y < o;}
				bool IsXMore(T o) { return m_x > o;}
				bool IsYMore(T o) { return m_y > o;}
				SDL_Rect ToSDL_Rect() { return { 0,0,(int)round(m_w),(int)round(m_h) };}
				SDL_Rect AsOriginOfSDL_Rect(int width, int height) { return { (int)round(m_x),(int)round(m_y), width, height }; }
				SDL_Rect AsOriginOfSDL_Rect(Vec2 o) { return { (int)round(m_x),(int)round(m_y),(int)round(o.m_x),(int)round(o.m_y) };}
				Vec2 AbsDist  ( Vec2 o) { return { tabs(m_x - o.m_x), tabs(m_y - o.m_y) };}
				Vec2 Dist     ( Vec2 o) { return {     (m_x - o.m_x),     (m_y - o.m_y) };}
				Vec2 Normalize()        { return *this / sqrt(this->Fleng()); }
				Vec2 Norm()             { return *this / sqrt(this->Fleng()); }
				static Vec2 PosFromSDL_Rect(SDL_Rect rect) {return { (T)rect.x, (T)rect.y};}
				double Fleng() {return m_x * m_x + m_y * m_y;}	
				Vec2 operator*(Vec2 o) {
					Vec2 temp;
					temp.m_x = m_x * o.m_x;
					temp.m_y = m_y * o.m_y;
					return temp;
				}
				Vec2 operator/(Vec2 o) {
					Vec2 temp;
					temp.m_x = m_x / o.m_x;
					temp.m_y = m_y / o.m_y;
					return temp;
				}
				Vec2 operator+(Vec2 o) {
					Vec2 temp;
					temp.m_x = m_x + o.m_x;
					temp.m_y = m_y + o.m_y;
					return temp;
				}
				Vec2 operator-(Vec2 o) {
					Vec2 temp;
					temp.m_x = m_x - o.m_x;
					temp.m_y = m_y - o.m_y;
					return temp;
				}
				Vec2 operator-(T o) {
					//this is a short hand for this - {o,o}; 
					Vec2 temp;
					temp.m_x = m_x - o;
					temp.m_y = m_y - o;
					return temp;
				}
				Vec2 operator+(T o) {
					//this is a short hand for this - {o,o}; 
					Vec2 temp;
					temp.m_x = m_x + o;
					temp.m_y = m_y + o;
					return temp;
				}
				Vec2 operator/(T i) {
					Vec2 temp;
					temp.m_x = m_x / i;
					temp.m_y = m_y / i;
					return temp;
				}
				Vec2 operator*(T i) {
					Vec2 temp;
					temp.m_x = m_x * i;
					temp.m_y = m_y * i;
					return temp;
				}
				void operator*=(Vec2 o) {
					m_x *= o.m_x;
					m_y *= o.m_y;
				}
				void operator*=(T i) {
					m_x *= i;
					m_y *= i;
				}
				void operator/=(Vec2 o) {
					m_x  /= o.m_x;
					m_y  /= o.m_y;
				}
				void operator/=(T i) {
					m_x /= i;
					m_y /= i;
				}
				void operator-=(Vec2 o) {
					m_x -= o.m_x;
					m_y -= o.m_y;
				}
				void operator+=(Vec2 o) {
					m_x += o.m_x;
					m_y += o.m_y;
				}						  
				void operator-=(T o) {
					// this is not technically a valid operation in LA but this is a short hand for
					// this - [o,o] wich is so that is why I implement it. 
					m_x -= o;
					m_y -= o;
				}
				void operator+=(T o) {
					// this is not technically a valid operation in LA but this is a short hand for
					// this + [o,o] wich is so that is why I implement it. 
					m_x += o;
					m_y += o;
				}
				void operator=(Vec2 o) {
					m_x = o.m_x;
					m_y = o.m_y;
				}
				void operator=(T o) {
					m_x = o;
					m_y = o;
				}
				bool operator==(Vec2 o) { return (m_x == o.m_x) && (m_y == o.m_x);  }
				bool operator!=(Vec2 o) { return !(*this == o);}
				bool operator<(Vec2 o)  { return (m_x < o.m_x) && (m_y < o.m_y); }
				bool operator>(Vec2 o)  { return (m_x > o.m_x) && (m_y > o.m_y); }
			};
			typedef Vec2<double> Vec2d;
			typedef Vec2<int> Vec2i;
			typedef Vec2<float> Vec2f;
			typedef Vec2<long> Vec2l;
			typedef Vec2<unsigned long> Vec2u;
		}
	}
}
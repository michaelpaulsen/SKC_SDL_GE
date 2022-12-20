#pragma once
#include <SDL.h>
#include <math.h>
namespace Skele_lib {
	namespace SKGE {
		namespace Vector {
			struct Vec2d {
				union {
					double m_x, m_w;
				};
				union {
					double m_y, m_h;
				};

				Vec2d(double x, double y) {
					m_x = x;
					m_y = y;
				}
				Vec2d() {
					m_x = 0;
					m_y = 0;
				}
				bool IsXLess(Vec2d o) {
					return m_x < o.m_x; 
				}
				bool IsYLess(Vec2d o) {
					return m_y < o.m_y; 
				}
				bool IsXMore(Vec2d o) {
					return m_x > o.m_x; 
				}
				bool IsYMore(Vec2d o) {
					return m_y > o.m_y; 
				}
				SDL_Rect ToSDL_Rect() {
					//makes a sdl rect object at the origin and the width and height set to m_x and m_y respectivly; 
					return { 0,0,(int)round(m_x),(int)round(m_y) }; //for some reason the c math lib has no way of casting to int with round (iround)
				}
				SDL_Rect AsOriginOfSDL_Rect(int width, int height) {
					//takes in a width and a height and makes a rect at the point of the vector \
					with the width and height passed in 
					return { (int)round(m_x),(int)round(m_y), width, height };
				}
				SDL_Rect AsOriginOfSDL_Rect(Vec2d o) {
					//takes in another vec2d and returns a rect with the origin set to this vector's endpoint \
					and the width set to the x value of the passed in vector \
					and the height the y value of the passed in vector
					return { (int)round(m_x),(int)round(m_y),(int)round(o.m_x),(int)round(o.m_y) };
				}
				Vec2d AbsDist(Vec2d o) {
					//  returns the absolute distance between this vector's enpoint and the other vecors enpoint   
					return { fabs(m_x - o.m_x), fabs(m_y - o.m_y) };
				}
				Vec2d Dist(Vec2d o) {
					//returns the signed distance between this vector's enpoint and the other vecors enpoint
					return { (m_x - o.m_x), (m_y - o.m_y) };
				}
				static Vec2d PosFromSDL_Rect(SDL_Rect rect) {
					return { (double)rect.x, (double)rect.y };
				}
				double Fleng() {
					return m_x * m_x + m_y * m_y;
					//get the f(ast) leng(th) of this vector
				}
				Vec2d operator*(Vec2d o) {
					Vec2d temp;
					temp.m_x = m_x * o.m_x;
					temp.m_y = m_y * o.m_y;
					return temp;
				}
				Vec2d operator/(Vec2d o) {
					Vec2d temp;
					temp.m_x = m_x / o.m_x;
					temp.m_y = m_y / o.m_y;
					return temp;
				}
				Vec2d operator+(Vec2d o) {
					Vec2d temp;
					temp.m_x = m_x + o.m_x;
					temp.m_y = m_y + o.m_y;
					return temp;
				}
				Vec2d operator-(Vec2d o) {
					Vec2d temp;
					temp.m_x = m_x - o.m_x;
					temp.m_y = m_y - o.m_y;
					return temp;
				}
				Vec2d operator-(double o) {
					//this is a short hand for this - {o,o}; 
					Vec2d temp;
					temp.m_x = m_x - o;
					temp.m_y = m_y - o;
					return temp;
				}
				Vec2d operator+(double o) {
					//this is a short hand for this - {o,o}; 
					Vec2d temp;
					temp.m_x = m_x + o;
					temp.m_y = m_y + o;
					return temp;
				}
				Vec2d operator/(double i) {
					Vec2d temp;
					temp.m_x = m_x / i;
					temp.m_y = m_y / i;
					return temp;
				}
				Vec2d operator*(double i) {
					Vec2d temp;
					temp.m_x = m_x * i;
					temp.m_y = m_y * i;
					return temp;
				}
				void operator*=(Vec2d o) {
					m_x *= o.m_x;
					m_y *= o.m_y;
				}
				void operator*=(double i) {
					m_x *= i;
					m_y *= i;
				}
				void operator/=(Vec2d o) {
					m_x  /= o.m_x;
					m_y  /= o.m_y;
				}
				void operator/=(double i) {
					m_x /= i;
					m_y /= i;
				}
				void operator-=(Vec2d o) {
					m_x -= o.m_x;
					m_y -= o.m_y;
				}
				void operator+=(Vec2d o) {
					m_x += o.m_x;
					m_y += o.m_y;
				}						  
				void operator-=(double o) {
					// this is not technically a valid operation in LA but this is a short hand for
					// this - [o,o] wich is so that is why I implement it. 

					m_x -= o;
					m_y -= o;
				}
				void operator+=(double o) {
					// this is not technically a valid operation in LA but this is a short hand for
					// this + [o,o] wich is so that is why I implement it. 

					m_x += o;
					m_y += o;
				}
				void operator=(Vec2d o) {
					m_x = o.m_x;
					m_y = o.m_y;
				}
				void operator=(double o) {
					m_x = o;
					m_y = o;
				}
				bool operator==(Vec2d o) {
					return (m_x == o.m_x) && (m_y == o.m_x);
				}
				bool operator!=(Vec2d o) {
					return !(*this == o);
				}
				bool operator<(Vec2d o) {
					return (m_x < o.m_x) && (m_y < o.m_y);
				}
				bool operator<(Vec2d o) {
					return (m_x > o.m_x) && (m_y > o.m_y);
				}
			};
		}
	}
}
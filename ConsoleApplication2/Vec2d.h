#pragma once
#include <SDL.h>
#include <math.h>
namespace Skele_lib {
	namespace SKGE {

		struct vec2d {
			double x, y;

			SDL_Rect ToSDL_Rect() {
				//makes a sdl rect object at the origin and the width and height set to x and y respectivly; 
				return { 0,0,(int)round(x),(int)round(y) }; //for some reason the c math lib has no way of casting to int with round (iround)

			}
			SDL_Rect AsOriginOfSDL_Rect(int width, int height) {
				//takes in a width and a height and makes a rect at the point of the vector \
				with the width and height passed in 
				return { (int)round(x),(int)round(y), width, height };
			}
			SDL_Rect AsOriginOfSDL_Rect(vec2d o) {
				//takes in another vec2d and returns a rect with the origin set to this vector's endpoint \
				and the width set to the x value of the passed in vector \
				and the height the y value of the passed in vector
				return { (int)round(x),(int)round(y),(int)round(o.x),(int)round(o.y) };
			}
			vec2d AbsDist(vec2d o) {
				//  returns the absolute distance between this vector's enpoint and the other vecors enpoint   
				return { fabs(x - o.x), fabs(y - o.y) };
			}
			vec2d Dist(vec2d o) {
				//returns the signed distance between this vector's enpoint and the other vecors enpoint
				return { (x - o.x), (y - o.y) };
			}
			static vec2d PosFromSDL_Rect(SDL_Rect rect) {
				return { (double)rect.x, (double)rect.y };
			}
			double Fleng() {
				return x * x + y * y;
				//get the f(ast) leng(th) of this vector
			}
			[[deprecated("use of the fast length api (fleng()) is recomended over this because it dosn't do the expensive sqrt this is here for completness")]]
			double leng() {
				return sqrt(x * x + y * y);
				//returns the slow length this should not be used 
				// exept when you need to sqrt the result anyway 
				// [this is marked depercated because there isn't a time that this should be used over fleng()]
			}
			vec2d operator*(vec2d o)  {
				vec2d temp; 
				temp.x = x * o.x;
				temp.y = y * o.y;
				return temp; 
			}
			
			vec2d operator/(vec2d o)  {
				vec2d temp;
				temp.x = x / o.x;
				temp.y = y / o.y;
				return temp;
			}
			
			vec2d operator+(vec2d o)  {
				vec2d temp;
				temp.x = x + o.x;
				temp.y = y + o.y;
				return temp;
			}
			vec2d operator-(vec2d o) {
				vec2d temp;
				temp.x = x - o.x;
				temp.y = y - o.y;
				return temp;
			}
			vec2d operator/(double i) {
				vec2d temp;
				temp.x = x / i;
				temp.y = y / i;
				return temp;
			}
			vec2d operator*(double i) {
				vec2d temp;
				temp.x = x * i;
				temp.y = y * i;
				return temp;
			}

			void operator*=(vec2d o) {
				x = x * o.x;
				y = y * o.y;
			}
			void operator*=(double i) {
				x = x * i;
				y = y * i;
			}
			void operator/=(vec2d o) {
				x = x / o.x;
				y = y / o.y;
			}
			void operator/=(double i) {
				x = x / i;
				y = y / i;
			}
			void operator-=(vec2d o) {
				x = x - o.x;
				y = y - o.y;
			}
			void operator+=(vec2d o) {
				x = x + o.x;
				y = y + o.y;
			}
			
		};
	}
}
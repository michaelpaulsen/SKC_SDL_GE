#pragma once
#include "sprite.h"
#include "Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		struct Player{
			Sprite sprite;
			vec2d position; 
			vec2d size; 
			int	score;
			Player(const char* path, SDL_Renderer* renderer, vec2d _s, vec2d _p = { 0,0 }) {
				vec2d rect = { _s.x,_s.y };
				sprite = Sprite(path, renderer, rect);
				position = { 0,0 }; 
				size = _s;
				score = 0; 
			}
			SDL_Rect getPlayerRect() {
				return { (int)position.x,(int)position.y, (int)size.x, (int)size.y };	
			}
		};
	}
}

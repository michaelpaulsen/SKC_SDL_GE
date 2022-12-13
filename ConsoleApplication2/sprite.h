#pragma once
#include<SDL.h>
#include<stdio.h>
#include "./Vec2d.h" 
class Sprite {
	SDL_Surface *surface = nullptr;
	SDL_Rect lastScaleRect; 
public:
	Sprite(const char* path, SDL_Surface* windowSurface) {
		SDL_Surface* loadedSurface = SDL_LoadBMP(path);
		lastScaleRect = { 0,0,0,0 }; 
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else
		{
			surface = SDL_ConvertSurface(loadedSurface, windowSurface->format, 0);
			if (surface == NULL)
			{
				printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
			}
			SDL_FreeSurface(loadedSurface);
		}
	}
	void DrawSprite(SDL_Rect pos, SDL_Surface* windowSurface) {
		SDL_BlitScaled(surface, NULL, windowSurface, &pos);
		lastScaleRect = pos; 
	}
	SDL_Surface *getSurface() {
		return this->surface; 
	}
	SDL_Rect getLastScaleRect() {
		return this->lastScaleRect; 
	}
	vec2d GetPosition(){
		return vec2d::PosFromSDL_Rect(this->lastScaleRect);
	}
};

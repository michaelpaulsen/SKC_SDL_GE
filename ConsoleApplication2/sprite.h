#pragma once
#include<SDL.h>
#include<stdio.h>
#include "./Vec2d.h" 
class Sprite {
	SDL_Texture* m_texture = NULL;
	SDL_Rect m_lastPos, m_lastUV; 
public:
	Sprite(const char* path, SDL_Surface* windowSurface, SDL_Renderer* renderer) {
		SDL_Surface* surface = nullptr;

		SDL_Surface* loadedSurface = SDL_LoadBMP(path);
		m_lastPos = { 0,0,0,0 }; 
		m_lastUV = { 0,0,0,0 }; 
		if (loadedSurface == NULL)
		{
			printf("Unable to load image %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else
		{
			m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (m_texture == NULL)
			{
				printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			}
			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}
	}
	void DrawSprite(SDL_Surface* windowSurface, SDL_Renderer* renderer, SDL_Rect* srcpos,  SDL_Rect* destpos) {
		SDL_RenderCopy(renderer, this->m_texture, srcpos, destpos);
		if (srcpos) {
			m_lastUV = *srcpos;
		}
		if (destpos) {
			m_lastPos = *destpos;
		}
	}
	SDL_Texture *getTexture() {
		return this->m_texture; 
	}
};

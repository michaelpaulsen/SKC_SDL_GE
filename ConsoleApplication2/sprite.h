#pragma once
#include<SDL.h>
#include<stdio.h>
#include "./Vec2d.h" 
namespace Skele_lib {
	namespace SKGE {
		class Sprite {
			SDL_Texture* m_texture = NULL;
			SDL_Rect m_lastPos, m_lastUV;
			vec2d m_size;
		public:
			Sprite(const char* path, SDL_Renderer* renderer) {
				m_size = { 0,0 }; 
				SDL_Surface* loadedSurface = SDL_LoadBMP(path);
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
					SDL_FreeSurface(loadedSurface);
				}
				m_lastPos = { 0,0,0,0 };
				m_lastUV = { 0,0,0,0 };
				m_size = size;
			}
			void DrawSprite( SDL_Renderer* renderer, SDL_Rect* srcpos, SDL_Rect* destpos) {
				SDL_RenderCopy(renderer, this->m_texture, srcpos, destpos);
				if (srcpos) {
					m_lastUV = *srcpos;
				}
				if (destpos) {
					m_lastPos = *destpos;
				}
			}
		};
	}
}
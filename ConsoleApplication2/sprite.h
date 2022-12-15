#pragma once
#include<SDL.h>
#include<stdio.h>
#include "./Vec2d.h" 
namespace Skele_lib {
	namespace SKGE {
		class Sprite {
			SDL_Texture* m_texture = NULL;
			vec2d m_size;
		public:
			Sprite() {
				m_size = { 0,0 }; 
			}
			Sprite(const char* path, SDL_Renderer* renderer, vec2d size = {0,0}) {
				SDL_Surface* loadedSurface = SDL_LoadBMP(path);
				if (loadedSurface != NULL)
				{
					m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
					SDL_FreeSurface(loadedSurface);
				}
				m_size = size;
			}
			void DrawSprite( SDL_Renderer* renderer, SDL_Rect* srcpos, SDL_Rect* destpos) {
				SDL_RenderCopy(renderer, this->m_texture, srcpos, destpos);
			}
		};
	}
}
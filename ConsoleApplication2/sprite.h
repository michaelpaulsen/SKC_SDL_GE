#pragma once
#include<SDL.h>
#include<stdio.h>
#include "./Vec2d.h" 
namespace Skele_lib {
	namespace SKGE {
		class Sprite {
			SDL_Texture* m_texture = NULL;
			Vec2d m_size, m_baseSize;
			SDL_Rect* p_UVMap;
		public:
			Sprite() {
				m_size = m_baseSize = { 0,0 };
				p_UVMap = NULL;
			}
			Sprite(const char* path, SDL_Renderer* renderer, Vec2d size) {
				SDL_Surface* loadedSurface = SDL_LoadBMP(path);
				
				p_UVMap = NULL;
				if (loadedSurface != NULL)
				{
					m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
					SDL_FreeSurface(loadedSurface);
				}
				m_size = m_baseSize = size;
			}
		
			void DrawSprite( SDL_Renderer* renderer, Vec2d pos) {
				SDL_Rect destrect = { pos.m_x, pos.m_y, m_size.m_x,m_size.m_y }; 
				printf("size [w,h] (%f, %f)\n", m_size.m_x, m_size.m_y);
				SDL_RenderCopy(renderer, this->m_texture, p_UVMap, &destrect);
			}
			void SetUVMap(SDL_Rect uvm) {
				if (!p_UVMap) {
					p_UVMap = (SDL_Rect*)malloc(sizeof(SDL_Rect));
					if (!p_UVMap)return;
				}
				p_UVMap->x = uvm.x;
				p_UVMap->y = uvm.y; 
				p_UVMap->w = uvm.w; 
				p_UVMap->h = uvm.h; 
			}
			void ClearUVMap() {
				free(p_UVMap);
			}
			void SetScale(double scale) {
				m_size *= scale; 
			}
			void ClearScale() {
				m_size = m_baseSize; //this is why we have m_baseSize 
			}
		};
	}
}
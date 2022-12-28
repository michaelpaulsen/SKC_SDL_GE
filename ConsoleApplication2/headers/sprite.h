#pragma once
#include<SDL.h>
#include<stdio.h>
#include "./Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		class Sprite {
			SDL_Texture* m_texture = NULL;
			Vector::Vec2d m_scale,  m_size; 
			SDL_Rect* p_UVMap;
		public:
			Sprite() {
				 m_size = 0;
				p_UVMap = NULL;
			}
			Sprite(const char* path, SDL_Renderer* renderer, Vector::Vec2d size) {
				SDL_Surface* loadedSurface = SDL_LoadBMP(path);
				
				p_UVMap = NULL;
				if (loadedSurface != NULL)
				{
					m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
					SDL_FreeSurface(loadedSurface);
				}
				m_size  =  size;
				m_scale = 1;
			}
			void DrawSprite( SDL_Renderer* renderer, int posx, int posy) {
				Vector::Vec2d realSize = m_scale * m_size;
				SDL_Rect destrect = { posx, posy, realSize.m_w,realSize.m_h };
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
			
			void SetXYScale(double scale) {
				m_scale.m_x = scale;
				m_scale.m_y = scale;
			}
			void GetScale(double& xScale, double& yScale) {
				xScale = m_size.m_x;
				yScale = m_size.m_y;
			}
			void SetXScale(double scale) {
				m_scale.m_x = scale; 
			}
			void SetYScale(double scale) {
				m_scale.m_y = scale; 
			}
			void ClearScale() {
				m_scale.m_x = 1;  
				m_scale.m_y = 1;  
			}
		};
	}
}
#pragma once
#include<SDL.h>
#include<stdio.h>
namespace Skele_lib {
	namespace SKGE {
		class Sprite {
			SDL_Texture* m_texture = NULL;
			double m_size_x, m_scale_x, m_size_y, m_scale_y;
			SDL_Rect* p_UVMap;
		public:
			Sprite() {
				 m_scale_x = m_size_x = m_scale_y = m_size_y = 0;
				p_UVMap = NULL;
			}
			Sprite(const char* path, SDL_Renderer* renderer, double sizex, double sizey) {
				SDL_Surface* loadedSurface = SDL_LoadBMP(path);
				
				p_UVMap = NULL;
				if (loadedSurface != NULL)
				{
					m_texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
					SDL_FreeSurface(loadedSurface);
				}
				m_size_x = m_size_y = sizey;
				m_scale_x = m_scale_y = 1;
			}
			void DrawSprite( SDL_Renderer* renderer, int posx, int posy) {
				double sizex, sizey;
				sizex = m_scale_x * m_size_x;
				sizey = m_scale_y * m_size_y;
				SDL_Rect destrect = { posx, posy, sizex,sizey};
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
				m_scale_x = scale;
				m_scale_y = scale;
			}
			void GetScale(double& xScale, double& yScale) {
				xScale = m_size_x;
				yScale = m_size_y;
			}
			void SetXScale(double scale) {
				m_scale_x = scale; 
			}
			void SetYScale(double scale) {
				m_scale_y = scale; 
			}
			void ClearScale() {
				m_scale_x = 1;  
				m_scale_y = 1;  
			}
		};
	}
}
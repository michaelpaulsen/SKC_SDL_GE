#pragma once
#include<SDL.h>
#include<stdio.h>
namespace Skele_lib {
	namespace SKGE {
		class Sprite {
			SDL_Texture* m_texture = NULL;
			double m_size_x, m_baseSize_x, m_size_y, m_baseSize_y;
			SDL_Rect* p_UVMap;
		public:
			Sprite() {
				 m_baseSize_x = m_size_x = m_baseSize_y = m_size_y = 0;
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
				
				m_size_x = m_baseSize_x = sizex;
				m_size_y = m_baseSize_y = sizey;
			}
		
			void DrawSprite( SDL_Renderer* renderer, int posx, int posy) {
				SDL_Rect destrect = { posx, posy, m_size_x,m_size_y};
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
				m_size_x *= scale;
				m_size_y *= scale;
			}
			void GetScale(double& xScale, double& yScale) {
				xScale = m_size_x;
				yScale = m_size_y;
			}
			void ClearScale() {
				m_size_x = m_baseSize_x; //this is why we have m_baseSize 
				m_size_y = m_baseSize_y; //this is why we have m_baseSize 
			}
		};
	}
}
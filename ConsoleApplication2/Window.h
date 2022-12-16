#pragma once
#include <SDL.h>
#include "./vec3d.h"
#include "Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		struct Window {
			SDL_Window* window = NULL;
			SDL_Renderer* renderer = NULL;
			Vector::Vec2d WindowSize;
			Vector::Vec3d lastColor;
			char lastAlpha; 
			Window(const char* title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags) {
				window = SDL_CreateWindow(title, x, y, w, h, windowFlags);
				renderer = SDL_CreateRenderer(window, -1, rendererFlags);
				WindowSize.m_x = w; 
				WindowSize.m_y = h;
				lastAlpha = 0; 
			}
			~Window() {
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window); 
			}
			void ClearRenderer() {
				SDL_RenderClear(renderer);
			}
			void UpdateScreen() {
				SDL_RenderPresent(renderer); 
			}
			void SetDrawColor(char r, char g, char b, char a = 255) {
				SDL_SetRenderDrawColor(renderer, r, g, b, a);
				lastColor.r = r; 
				lastColor.g = g; 
				lastColor.b = b;
				lastAlpha   = a;
			}
			SDL_Rect WindowSizeToSdlRect() {
				return { 0,0, (int)WindowSize.m_x,(int)WindowSize.m_y };
			}
			void ClearScreenToDrawColor() {
				auto r = WindowSizeToSdlRect(); 
				SDL_RenderFillRect(renderer, &r);
			}
		};
	}
}
#pragma once
#include <SDL.h>
#include "./vec3d.h"
#include "Vec2d.h"
namespace Skele_lib {
	namespace SKGE {
		struct Window {
            typedef unsigned char ucolor_t; 
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
			void SetDrawColor(ucolor_t r, ucolor_t g, ucolor_t b, ucolor_t a = 255) {
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
            int RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
                int offsetx, offsety, d;
                int status;
                offsetx = 0;
                offsety = radius;
                d = radius - 1;
                status = 0;
                while (offsety >= offsetx) {
                    status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
                    status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
                    status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
                    status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
                    status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
                    status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
                    status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
                    status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);
                    if (status < 0) {
                        status = -1;
                        break;
                    }
                    if (d >= 2 * offsetx) {
                        d -= 2 * offsetx + 1;
                        offsetx += 1;
                    }
                    else if (d < 2 * (radius - offsety)) {
                        d += 2 * offsety - 1;
                        offsety -= 1;
                    }
                    else {
                        d += 2 * (offsety - offsetx - 1);
                        offsety -= 1;
                        offsetx += 1;
                    }
                }
                return status;
            }
            int RenderFillCircle(int x, int y, int radius) {
                int offsetx, offsety, d;
                int status;
                offsetx = 0;
                offsety = radius;
                d = radius - 1;
                status = 0;
                while (offsety >= offsetx) {
                    status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                        x + offsety, y + offsetx);
                    status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                        x + offsetx, y + offsety);
                    status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                        x + offsetx, y - offsety);
                    status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                        x + offsety, y - offsetx);
                    if (status < 0) {
                        status = -1;
                        break;
                    }
                    if (d >= 2 * offsetx) {
                        d -= 2 * offsetx + 1;
                        offsetx += 1;
                    }
                    else if (d < 2 * (radius - offsety)) {
                        d += 2 * offsety - 1;
                        offsety -= 1;
                    }
                    else {
                        d += 2 * (offsety - offsetx - 1);
                        offsety -= 1;
                        offsetx += 1;
                    }
                }
                return status;
            }
            int RenderFillRect(int x, int y, int w, int h) {
                SDL_Rect rect = { x,y,w,h }; 
                SDL_RenderFillRect(renderer, &rect);
            }
		};
	}
}
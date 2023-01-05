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
            void RenderFilledCircle(SDL_Renderer* renderer, double tx, double ty, double r) {
                double topbound = ty - r;
                double bottombound = ty + r;
                double leftbound = tx - r;
                double rightbound = tx + r;
                for (double y = topbound; y < bottombound; y++) {
                    for (double x = leftbound; x < rightbound; x++) {
                        double dx = (tx - x);
                        double dy = (ty - y);
                        if (dx * dx + dy * dy <= r * r) {
                            SDL_RenderDrawPoint(renderer, x, y);
                        }
                    }
                }
            }
            void  RenderDrawCircle(int x, int y, int radius) {
                int offsetx, offsety, d;
                int status;
                offsetx = 0;
                offsety = radius;
                d = radius - 1;
                status = 0;
                while (offsety >= offsetx) {
                     SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
                     SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
                     SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
                     SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
                     SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
                     SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
                     SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
                     SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);
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
            }
            int RenderFillRect(int x, int y, int w, int h) {
                SDL_Rect rect = { x,y,w,h }; 
                SDL_RenderFillRect(renderer, &rect);
            }
            void RenderDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3){
                SDL_RenderDrawLine(renderer, x1, y1, x2, y2); 
                SDL_RenderDrawLine(renderer, x2, y2, x3, y3); 
                SDL_RenderDrawLine(renderer, x1, y1, x3, y3); 
            }
            void RenderDrawLines(SDL_Point* pos, const size_t count) {
                SDL_RenderDrawLines(renderer, pos, count);
            }

		};
	}
}
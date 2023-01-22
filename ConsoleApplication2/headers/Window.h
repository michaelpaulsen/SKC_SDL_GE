#pragma once
#include <SDL.h>
#include "./vec3d.h"
#include "Vec2d.h"
#include "Defines.h"

namespace Skele_lib {
	namespace SKGE {
		class Window {
            typedef unsigned char ucolor_t; 
			SDL_Window* window = NULL;
            std::string windowTitle; 
			SDL_Renderer* renderer = NULL;
			Vector::Vec2i windowSize;
			Vector::Vec3d lastColor;
            bool m_isPaused = false, m_isInInvintory = false;
            size_t m_activeInvintory;
            char lastAlpha;
        public :
            Window(std::string title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags) {
                windowTitle = title;
                window = SDL_CreateWindow(title.c_str(), x, y, w, h, windowFlags);
                renderer = SDL_CreateRenderer(window, -1, rendererFlags);
                windowSize = { w,h };
                lastAlpha = 0;
            }
            ~Window() {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
            }

            SDL_Window* const GetWindow() const                     { return        window;               }
            Vector::Vec2i     GetWindowSize() const                 { return        windowSize;           }
            size_t            GetActiveInvinory() const             { return m_activeInvintory;           }
            bool              IsPaused() const                      { return        m_isPaused;           }
            bool              IsInInvintory() const                 { return   m_isInInvintory;           }
            void              SetPuase(bool p)                      { m_isPaused = p;                     }
            void              TogglePause()                         { m_isPaused = m_isPaused?false:true; }
            void              SetWindowTitle(const std::string str) { SetWindowTitle(str.c_str());        }
            void              SetWindowTitle(const char* title) {
                windowTitle = title;
                SDL_SetWindowTitle(window, title);
            }
            void              ToggleInvintory(size_t pid = 0, bool puseGame = true) {
                m_activeInvintory = pid;
                m_isInInvintory = !m_isInInvintory;
            }
            void              ClearRenderer() {
				SDL_RenderClear(renderer);
			}
			void              UpdateScreen() {
				SDL_RenderPresent(renderer); 
			}
			void              SetDrawColor(ucolor_t r, ucolor_t g, ucolor_t b, ucolor_t a = 255) {
				SDL_SetRenderDrawColor(renderer, r, g, b, a);
				lastColor.r = r; 
				lastColor.g = g; 
				lastColor.b = b;
				lastAlpha   = a;
			}
            void              SetSize(Vector::Vec2i &wind) {     
                SDL_GetWindowSize(window, &wind.m_w, &wind.m_h);
                windowSize = { wind.m_w, wind.m_h };
            }
            SDL_Rect          WindowSizeToSdlRect() {
				return { 0,0, (int)windowSize.m_x,(int)windowSize.m_y };
			}
			void              ClearScreenToDrawColor() {
				auto r = WindowSizeToSdlRect(); 
				SDL_RenderFillRect(renderer, &r);
			}
            void              RenderFilledCircle( double tx, double ty, double r) {
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
            void              RenderDrawCircle(int x, int y, int radius) {
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
            void              RenderFillRect(int x, int y, int w, int h) {
                SDL_Rect rect = { x,y,w,h }; 
                SDL_RenderFillRect(renderer, &rect);
            }
            void              RenderDrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3){
                SDL_RenderDrawLine(renderer, x1, y1, x2, y2); 
                SDL_RenderDrawLine(renderer, x2, y2, x3, y3); 
                SDL_RenderDrawLine(renderer, x1, y1, x3, y3); 
            }
            void              RenderDrawLines(SDL_Point* pos, const size_t count) {
                SDL_RenderDrawLines(renderer, pos, count);
            }
            void              RenderDrawRect(int x, int y, int w, int h) {
                SDL_Rect r = { x,y,w,h };
                SDL_RenderDrawRect(renderer, &r);
            }
            void              DrawInventory(int cols, int rows) {
                static bool debug = true; 
                int w = ((float)windowSize.m_w/(float)cols-1);
                int h = ((float)windowSize.m_h/(float)rows-1);
                int x, y;
                int count = 0; 
                for (int r = 0; r < rows; r++) {
                    for (int c = 0; c < cols; c ++) {
                        x = (c * w); 
                        y = (r * w);
                        if (count % 2 == 0) {
                            SetDrawColor(0x09, 0x09, 0x09);
                        }
                        else {
                            SetDrawColor(0xaa, 0xaa, 0xaa);
                        }
                        
                        RenderFillRect(x, y, w, h); 
                        SetDrawColor(0, 0, 0); 
                        RenderDrawRect(x, y, w, h);
                        count++;
                    }

                }
                debug = false; 
            }
            auto              TakeScreenShot() {
                auto surface = SDL_GetWindowSurface(window);
                auto now = std::chrono::system_clock::now();
                auto h = std::format("{:%H}", now);
                auto s = std::format("{:%S}", now);
                auto i = std::format("{:%M}", now);
                auto path = std::format("./screenshots/{}-{}.{}.{:0>2.2}.bmp", windowTitle, h, i, s);
                return SDL_SaveBMP(surface, path.c_str()); 
                //int SDL_SaveBMP(SDL_Surface * surface,
                //                const char* file)
            }
		};
	}
}
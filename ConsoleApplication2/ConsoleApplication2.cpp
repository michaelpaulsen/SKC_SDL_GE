#include <SDL.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "./EventHandler.h"
#include "./funtions.h"
#include "./Timer.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
Skele_lib::SKGE::EventQue eQue; 
uint64_t g_frameCount = 0, frame1 = 0, sleepTime = 0;
auto frameTime = std::chrono::milliseconds((int)(1000.0 / 60.0));
Skele_lib::SKGE::Timer::ElapsedTime_T fElapsedTime = 0.0; 
Skele_lib::SKGE::Timer::chrono_sysclock_t tp1, tp2; 
int main(int argc, char* args[])
{

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	auto gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Skele_lib::SKGE::Functions::registerDefaultEvents(eQue);
	auto sdlinitstate = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (sdlinitstate  < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return sdlinitstate; 
	}
	else
	{
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Event e;
			bool quit = false;
			tp1 = std::chrono::system_clock::now();
			while (!quit) {
				while (SDL_PollEvent(&e)) {
					if(e.type != SDL_QUIT){
						eQue.callEventByTID(e.type, e, fElapsedTime);
						continue;
					}
					quit = true; 
					
				}
				tp2 = std::chrono::system_clock::now();
				Skele_lib::SKGE::Timer::Wait(tp1, tp2, frameTime, fElapsedTime);
				if (g_frameCount % 16 == 0) {
					printf("time for frame %llu %f\n", g_frameCount, (float)((tp2-tp1).count())/1000.0); 
				}
				tp1 = tp2;
				g_frameCount++;
				//incriment the global frame count
			}
		}
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 0;
	}
	return -1;
}

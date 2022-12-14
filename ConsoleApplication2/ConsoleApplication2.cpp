#include <SDL.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "./EventHandler.h"
#include "./funtions.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
EventQue eQue; 
uint64_t frame = 0, frame1 = 0, sleepTime = 0;
auto frameTime = std::chrono::milliseconds((int)(1000.0 / 60.0));
long double fElapsedTime = 0.0; 
int main(int argc, char* args[])
{

	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	auto gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	registerDefaultEvents(eQue);
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
			std::chrono::time_point<std::chrono::system_clock> tp1 = std::chrono::system_clock::now();
			while (!quit) {
				while (SDL_PollEvent(&e)) {
					if(e.type != SDL_QUIT){
						eQue.callEventByTID(e.type, e, fElapsedTime);
					}
					else {
						quit = true; 
					}
					
				}
				std::chrono::time_point<std::chrono::system_clock> tp2 = std::chrono::system_clock::now();
				std::chrono::duration<float> difference = tp2 - tp1;
				tp1 = tp2;
				
				std::this_thread::sleep_for(frameTime - difference);
				fElapsedTime = difference.count(); 
				if (frame % 60 == 0 && frame) {
					printf("frame render time %f ms target frame time %llu\n", difference.count() * 1000, frameTime.count());
				}
				frame++;
			}
		}
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 0;
	}
	return -1;
}

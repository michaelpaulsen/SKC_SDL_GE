#include <SDL.h>
#include <stdio.h>
#include "./EventHandler.h"
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
EventQue eQue; 
int main(int argc, char* args[])
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	eQue.registerEvent("SDL_MOUSEMOTION", SDL_MOUSEMOTION, [](SDL_Event e) {
		// it is not technically safe to assume that this is a SDL_MOUSEMOTION event but the way that its called will dictate that it is.
		}
	);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
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
			while (!quit) {
				while (SDL_PollEvent(&e)) {
					if(e.type != SDL_QUIT){
						eQue.callEventByTID(e.type, e);
					}
					else {
						quit = true; 
					}
				}
			}
		}
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 0;
	}
	return -1;
}

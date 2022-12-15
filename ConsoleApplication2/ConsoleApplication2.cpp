#include <SDL.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "./EventHandler.h"
#include "./funtions.h"
#include "./Timer.h"
#include "./GameState.h"
#include "./Window.h"
#include "./sprite.h"

auto gameState = Skele_lib::SKGE::GameState(60);
Skele_lib::SKGE::Timer::chrono_sysclock_t tp1, tp2; 
Skele_lib::SKGE::EventQue eQue;
int main(int argc, char* args[]){
	SDL_Surface* screenSurface = NULL;
	Skele_lib::SKGE::Functions::registerDefaultEvents(eQue);
	auto sdlinitstate = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (sdlinitstate  < 0){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return sdlinitstate; 
	}
	auto window = Skele_lib::SKGE::Window("test",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480, SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED);
	if (window.window == NULL){
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return -255; 
	}
	auto sprite1 = Skele_lib::SKGE::Sprite("C:/Users/Skele/source/repos/SKC_SDL_GE/ConsoleApplication2/img/testSprite.bmp", window.renderer);

	SDL_Event e;
	bool quit = false;
	tp1 = std::chrono::system_clock::now();
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if(e.type != SDL_QUIT){		
				eQue.callEventByTID(e.type, e, gameState.fElapsedTime);
				continue;
			}
			quit = true; 
		}
		window.SetDrawColor(255, 255, 255);
		window.ClearScreenToDrawColor();
		window.UpdateScreen();
		tp2 = std::chrono::system_clock::now();
		Skele_lib::SKGE::Timer::Wait(tp1, tp2, gameState.GetFrameTime(), gameState.fElapsedTime);
		tp1 = tp2;
		gameState.frame++;
	}
	SDL_Quit();
	return 0;
}
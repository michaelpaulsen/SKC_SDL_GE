#include <SDL.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "./EventHandler.h"
#include "./funtions.h"
#include "./Timer.h"
#include "./world.h"
#include "./Window.h"
#include "./Player.h"

auto world = Skele_lib::SKGE::World(60);
Skele_lib::SKGE::Timer::chrono_sysclock_t tp1, tp2; 
Skele_lib::SKGE::EventQue eQue;


int main(int argc, char* args[]){
	SDL_Rect playerUV = { 0,0,16,16 };
	SDL_Rect playerPos = { 128,128,128,128 };
	auto window = Skele_lib::SKGE::Window("test",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1920, 1080,
		SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED);
	world.AddPlayer("C:/Users/Skele/source/repos/SKC_SDL_GE/ConsoleApplication2/img/testSprite.bmp", window.renderer, 64, 64, 0, 0);
	world.GetPlayerAt(0).SetUVMap({ 0,0,16,16 }); 
	world.AddPlayer("C:/Users/Skele/source/repos/SKC_SDL_GE/ConsoleApplication2/img/testSprite.bmp", window.renderer, 64, 64, 64, 0);
	world.GetPlayerAt(1).SetUVMap({ 16,0,16,16 });

	eQue.registerEvent("SDL_KEYDOWN",            SDL_KEYDOWN,            [](SDL_Event e, Skele_lib::SKGE::World &world) {
		auto sym = e.key.keysym.sym;
		double p_scaleX, p_scaleY;
		static int xpos = 0; 
		switch (sym) {
				case 'z': {
					auto& player = world.GetPlayerAt(0);
					xpos += 16; 
					xpos %= 32; 
					world.GetPlayerAt(0).SetUVMap({ xpos,0,16,16 });
					world.GetPlayerAt(0).SetXYScale(2);
					world.GetPlayerAt(0).GetScale(p_scaleX, p_scaleY);
					printf("size [w,h] (%f, %f)\n", p_scaleX, p_scaleY);

					return;
				}
				case 'x': {
					world.GetPlayerAt(0).ClearScale();
					world.GetPlayerAt(0).GetScale(p_scaleX, p_scaleY);
					printf("size [w,h] (%f, %f)\n", p_scaleX, p_scaleY);
					return;
				}
				default: {
					printf("un handled key %d (\"%c\")\n", sym, sym);
					return;
				}
			}
		});
	eQue.registerEvent("SDL_MOUSEMOTION",        SDL_MOUSEMOTION,        [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_WINDOWEVENT",        SDL_WINDOWEVENT,        [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_KEYDOWN",            SDL_KEYUP,              [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_TEXTEDITING",        SDL_TEXTEDITING,        [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_KEYMAPCHANGED",      SDL_KEYMAPCHANGED,      [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_AUDIODEVICEADDED",   SDL_AUDIODEVICEADDED,   [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_AUDIODEVICEREMOVED", SDL_AUDIODEVICEREMOVED, [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_MOUSEBUTTONDOWN",    SDL_MOUSEBUTTONDOWN,    [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_MOUSEBUTTONUP",      SDL_MOUSEBUTTONUP,      [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_MOUSEWHEEL",         SDL_MOUSEWHEEL,         [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_TEXTINPUT",          SDL_TEXTINPUT,          [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	eQue.registerEvent("SDL_KEYMAPCHANGED",      SDL_KEYMAPCHANGED,      [](SDL_Event e, Skele_lib::SKGE::World &world) {});
	auto sdlinitstate = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (sdlinitstate  < 0){
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return sdlinitstate; 
	}
	
	if (!(window.window && window.renderer)){
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return -255; 
	}
	SDL_Event e;
	bool quit = false;
	tp1 = std::chrono::system_clock::now();
	 
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if(e.type != SDL_QUIT){	
				eQue.callEventByTID(e.type, e, world);
				continue;
			}
			quit = true; 
		}
		///=== DRAW START ===
		window.SetDrawColor(255, 255, 255);		
		window.ClearScreenToDrawColor();
		///=== DRAW THINGS START ===
		world.DrawPlayers(window.renderer); 
		window.UpdateScreen();
		///=== DRAW END ===
		tp2 = std::chrono::system_clock::now();
		Skele_lib::SKGE::Timer::Wait(tp1, tp2, world.GetFrameTime(), world.fElapsedTime);
		tp1 = tp2;
		world.IncFrame();
	}
	SDL_Quit();
	return 0;
}
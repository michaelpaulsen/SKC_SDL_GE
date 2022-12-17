#include <SDL.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include "./headers/EventHandler.h"
#include "./headers/funtions.h"
#include "./headers/Timer.h"
#include "./headers/world.h"
#include "./headers/Window.h"
#include "./headers/Player.h"
auto world = Skele_lib::SKGE::World(60);
Skele_lib::SKGE::Timer::chrono_sysclock_t tp1, tp2; 
Skele_lib::SKGE::EventQue eQue;
int windw = 1920, windh = 1080;
size_t wFlags = SDL_WINDOW_SHOWN, rFlags = SDL_RENDERER_ACCELERATED;
int main(int argc, char* args[]){
	auto window = Skele_lib::SKGE::Window("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windw, windh,wFlags,rFlags);
	world.AddPlayer("C:/Users/Skele/source/repos/SKC_SDL_GE/ConsoleApplication2/img/testSprite.bmp", window.renderer, 64, 64, 0, 0,5,5);
	world.AddPlayer("C:/Users/Skele/source/repos/SKC_SDL_GE/ConsoleApplication2/img/testSprite.bmp", window.renderer, 64, 64, 64, 0,10,10);
	world.GetPlayerAt(0).SetUVMap({ 0,0,16,16 });
	world.GetPlayerAt(1).SetUVMap({ 16,0,16,16 });
	world.GetPlayerAt(0).SetDragForce(0.025);
	world.GetPlayerAt(1).SetDragForce(0.05);
	eQue.registerEvent("SDL_KEYDOWN",            SDL_KEYDOWN,            [](SDL_Event e, Skele_lib::SKGE::World &world) {
		auto sym = e.key.keysym.sym;
		static int xpos = 0; 
		static double scale = 1;
		static size_t targetPlayer = 0; 
		auto& player = world.GetPlayerAt(targetPlayer);
		auto playerRect = player.getPlayerRect();
		switch (sym) {
				case '=': {scale += 0.1; player.SetXYScale(scale); printf("scale %f%%\n", scale * 100); break;}
				case '-': {scale -= 0.1; player.SetXYScale(scale); printf("scale %f%%\n", scale * 100); break;}
				case 'f': {targetPlayer++; targetPlayer %= 2; printf("changing to player %llu ", targetPlayer); break; }
				case ' ': {player.ClearScale(); scale = 1.0; return;}
				case 'w': {player.AddForce(0,-100); return;}
				case 'a': {player.AddForce(-100,0); return;}
				case 's': {player.AddForce(0, 100); return;}
				case 'd': {player.AddForce(100, 0); return;}
				default: {printf("un handled key %d (\"%c\")\n", sym, sym); return;}
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
		world.ApplyForceToPlayers(windw, windh);
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
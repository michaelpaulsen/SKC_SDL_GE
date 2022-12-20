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
#include "./headers/Physics.h"
auto world = Skele_lib::SKGE::World(60);
Skele_lib::SKGE::Timer::chrono_sysclock_t tp1, tp2; 
Skele_lib::SKGE::EventQue eQue;
int windw = 1920, windh = 1080;
size_t wFlags = SDL_WINDOW_SHOWN, rFlags = SDL_RENDERER_ACCELERATED;
int main(int argc, char* args[]){
	auto window = Skele_lib::SKGE::Window("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windw, windh,wFlags,rFlags);
	world.AddPlayer("C:/Users/Skele/source/repos/SKC_SDL_GE/ConsoleApplication2/img/testSprite.bmp", window.renderer, { 64, 64 }, { 00, 00 }, { 00.025, 00.025 });
	world.AddPlayer("C:/Users/Skele/source/repos/SKC_SDL_GE/ConsoleApplication2/img/testSprite.bmp", window.renderer, { 64, 64 }, { 64, 00 }, { 00.500, 00.500 });
	world.GetPlayerAt(0).SetUVMap({ 0,0,16,16 });
	world.GetPlayerAt(1).SetUVMap({ 16,0,16,16 });
	eQue.registerEvent("SDL_KEYDOWN", { SDL_KEYDOWN, true }, [](const SDL_Event* e, Skele_lib::SKGE::World& world, size_t pid) {
		auto sym = e->key.keysym.sym;
		auto& player = world.GetPlayerAt(0);
		auto& spring = world.GetPlayerAt(1); 
		switch (sym) {
				case 'w': {
					Skele_lib::SKGE::Physics::AddForce(player.GetForce(),{ 0,-100 });
					return;
				}
				case 'a': {
					Skele_lib::SKGE::Physics::AddForce(player.GetForce(), { -100,0 });
					return;
				}
				case 's': {
					Skele_lib::SKGE::Physics::AddForce(player.GetForce(), { 0, 100 });
					return;
				}
				case 'd': {
					Skele_lib::SKGE::Physics::AddForce(player.GetForce(), { 100, 0 });
					return;
				}
				default: {
					return;
				}

			}
			});
	eQue.registerEvent("SDL_MOUSEMOTION",		        { SDL_MOUSEMOTION, true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_WINDOWEVENT",               { SDL_WINDOWEVENT, true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_KEYDOWN",                         { SDL_KEYUP, true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_TEXTEDITING",               { SDL_TEXTEDITING, true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_KEYMAPCHANGED",           { SDL_KEYMAPCHANGED, true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_AUDIODEVICEADDED",     { SDL_AUDIODEVICEADDED, true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_AUDIODEVICEREMOVED", { SDL_AUDIODEVICEREMOVED, true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_MOUSEBUTTONDOWN",        { SDL_MOUSEBUTTONDOWN,true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_MOUSEBUTTONUP",            { SDL_MOUSEBUTTONUP,true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_MOUSEWHEEL",                  { SDL_MOUSEWHEEL,true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_TEXTINPUT",			          { SDL_TEXTINPUT, true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("SDL_KEYMAPCHANGED",            { SDL_KEYMAPCHANGED,true}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) {});
	eQue.registerEvent("P_hit_top_bound",                            { 0, false}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) { printf("player %llu hit the         top of the world\n",pid+1); });
	eQue.registerEvent("P_hit_bottom_bound",                         { 0, false}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) { printf("player %llu hit the      bottom of the world\n",pid+1); });
	eQue.registerEvent("P_hit_left_bound",                           { 0, false}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) { printf("player %llu hit the left  bound of the world\n",pid+1); });
	eQue.registerEvent("P_hit_right_bound",                          { 0, false}, [](const SDL_Event* e, Skele_lib::SKGE::World &world,size_t pid) { printf("player %llu hit the right bound of the world\n",pid+1); });
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
				eQue.callEventByTID({ e.type,true } , &e, world);
				continue;
			}
			quit = true; 
		}
		auto& player = world.GetPlayerAt(0);
		auto& spring = world.GetPlayerAt(1);
		Skele_lib::SKGE::Physics::CaculateAndAddSpringForce(spring.GetPosition(), player.GetPosition(), spring.GetForce(), 0.0025, 64);
		world.ApplyForceToPlayers();
		Skele_lib::SKGE::ColideWithWalls(windw, windh, eQue, world);

		world.BouncePlayersOffWorldBounds(windw, windh);
		
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
#define skc_W64
#include <SDL.h>
#include <chrono>
#include <random>
#include "headers/Counter.h"
#include "headers/Defines.h"
#include  "headers/LOGGER.h"
#include   "headers/Level.h"
#include   "headers/Timer.h"
#include   "headers/world.h"
#include     "headers/RNG.h"
int main(int argc, char* args[]) {
	auto level = Skele_lib::SKGE::Formats::Level("C:\\Users\\Skele\\source\\repos\\SKC_SDL_GE\\assets\\level.lvl");
	int mode = 0;
	///=== creating world ===  
	const int targetFPS = 60; 
	auto world = Skele_lib::SKGE::World(targetFPS);
	///=== creating frame limiting stuff ===
	Skele_lib::SKGE::Timer::chrono_sysclock_t tp1, tp2;
	Skele_lib::SKGE::EventQue eQue;
	///=== creating logging ===
	auto mdl = Skele_lib::SKGE::LOGGER("MAIN - DBUG");
	auto mel = Skele_lib::SKGE::LOGGER("MAIN - ERROR");
	auto mwl = Skele_lib::SKGE::LOGGER("MAIN - WARN");
	auto mil = Skele_lib::SKGE::LOGGER("MAIN - INFO");
	///=== creating window ===
	auto sdlinitstate = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	if (sdlinitstate < 0) {
		mel.Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return sdlinitstate;
	}
	///=== points ===
	SDL_Point points[3000] = { 0 };
	///=== create Event Timers ===
	auto triangleTimer = Skele_lib::SKGE::Counter();
	auto rectcounter = Skele_lib::SKGE::Counter();
	triangleTimer.setLeng(25);
	triangleTimer.setMax(100); 
	rectcounter.setLeng(10); 
	rectcounter.setMax(50); 
	///=== creating window ===
	int windw = 1080, windh = 1080;
	uint32_t wFlags = SDL_WINDOW_SHOWN |SDL_WINDOW_RESIZABLE, rFlags = SDL_RENDERER_ACCELERATED;
	auto window = Skele_lib::SKGE::Window("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windw, windh, wFlags, rFlags);
	///=== Set up the random number generator===
	int minr = 0, maxr = 100;
	int NUM_POINTS = 100;
	Skele_lib::SKGE::RNG rng;
	/// draw the frame
	bool drawFrame = true;
	bool showinv = false;
	bool minimized = false; 
	///=== registering the keydown event===
	eQue.registerEvent("TimerActiveTrigger",       { 0,                        false }, [mil, mwl, mdl, mel, &window, &showinv, &mode,  &eQue, &rectcounter](const SDL_Event* e, Skele_lib::SKGE::World& world, size_t pid) {
		switch (pid) {
			case 0: {
				window.RenderDrawTriangle(100, 100, 150, 150, 100, 150);
				window.RenderDrawTriangle(100, 100, 200, 200, 100, 200);
				break;
			}
			case 1: {
				window.RenderFillRect(32, 0, 32, 32);
				break;
			}
		}
	});
	eQue.registerEvent("TimerTriggerReset",        { 0,                        false }, [mil, mwl, mdl, mel, &window, &showinv, &mode,  &eQue, &rectcounter](const SDL_Event* e, Skele_lib::SKGE::World& world, size_t pid) {
		if (pid == 0) {
			window.RenderFilledCircle(16, 16, 16); 
			rectcounter(world, eQue); 
		}
	});
	eQue.registerEvent("SDL_KEYDOWN",              { SDL_KEYDOWN,              true  }, [mil, mwl, mdl, mel, &window, &showinv, &mode,  &eQue, &rectcounter](const SDL_Event* e, Skele_lib::SKGE::World& world, size_t pid) {
		auto sym = e->key.keysym.sym;
	switch (sym) {
	case 'q': {
		window.TogglePause();
		coutf("{:<100}\n", window.IsPaused() ? "window is paused" : "window is not paused");
		break;
	}
	case 'e': {
		showinv = !showinv;
		window.ToggleInvintory(0, true);
		break;
	}
	case 'm': {
		(++mode) %= 2;
	}
	default: {
		return;
	}

	}
	});
	eQue.registerEvent("SDL_RENDER_TARGETS_RESET", { SDL_RENDER_TARGETS_RESET, true }, [mil, mwl, mdl, mel, &window, &windh, &windw, &minimized](const SDL_Event* e, Skele_lib::SKGE::World& world, size_t pid) {

		window.SetSize();
		auto type = e->window.event; 
		if (type == SDL_WINDOWEVENT_MINIMIZED) minimized = true; 
		if (type == SDL_WINDOWEVENT_RESTORED || type == SDL_WINDOWEVENT_MAXIMIZED) minimized = false; 
	});
	///=== set up the random things that I don't have a better owner for===
	SDL_Event e;
	bool quit = false;
	///=== init the first time point===
	tp1 = std::chrono::system_clock::now();
	CBuffer(titlebuffer, 200); 
	///=== main loop ===
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			///=== poll the events ===
			if (e.type != SDL_QUIT) {
				eQue.callEventByTID({ e.type,true } , &e, world);
				continue;
			}
			quit = true;
		}
		///=== DRAW START ===
		if (drawFrame) {
			auto size = Skele_lib::SKGE::Vector::Vec2d();
			size.m_w = ((double)(windw/1) / (double)level.GetSize().m_w);
			size.m_h = ((double)(windh/1) / (double)level.GetSize().m_h);
			window.SetDrawColor(0xff, 0xff, 0xff);
			window.ClearScreenToDrawColor();
			for (size_t y = 0; y < level.GetSize().m_y; y++) {
				for (size_t x = 0; x < level.GetSize().m_y; x++) {
					int xpos = x * size.m_w;
					int ypos = y * size.m_h;
					switch (level.At(x, y)) {
						case 0: {
							window.SetDrawColor(100, 255, 100);
							break; 
						}
						case 1: {
							window.SetDrawColor(0, 0, 0);
							break; 
						}
						default: {
							window.SetDrawColor(255, 255, 255);
						}
					}
					window.RenderFillRect(xpos, ypos, size.m_w+1, size.m_h+1);
				}
			}
			window.UpdateScreen();
		}
		drawFrame = !(window.IsPaused() || minimized);
		///===================================
		///=== DRAW THINGS           START ===
		///world.DrawPlayers(window.renderer);
		///=== DRAW THINGS             END ===
		///=== DRAW                    END ===
		///=== Increment the frame counter ===
		///===================================
		auto titlestr = std::format("{} - {} fps drawing {} inv {}", "ENTER GAME TITLE HERE", 1.0 / world.dElapsedTime, drawFrame, showinv); 
#ifdef _DEBUG
		titlestr += " [DEBUG]"; 
#endif // _DEBUG

		window.SetWindowTitle(titlestr.c_str());
		world.IncFrame();
		///=== Frame Limit Start === 
		tp2 = std::chrono::system_clock::now();
		Skele_lib::SKGE::Timer::Wait(tp1, tp2, world.GetFrameTime(), world.dElapsedTime);
		tp1 = tp2;
	}
	///===quit the sdl instance===
	SDL_Quit();
	///===thank the player for playing===
	mil.Log("Thanks For Playing\n");
	return 0;
}
#define skc_W64
#include <SDL.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <random>
#include "./headers/EventHandler.h"
#include "./headers/funtions.h"
#include "./headers/Timer.h"
#include "./headers/world.h"
#include "./headers/Window.h"
#include "./headers/Player.h"
#include "./headers/Physics.h"
#include "./headers/LOGGER.h"
#include "./headers/RNG.h"
#include "./headers/Counter.h"
#include "./headers/KeyModifiers.h"
#define CBuffer(name, size) char name[size] 
#define clearBuffer(s, size, buffer) for(size_t s = 0; s < size; s++){buffer[s] = 0;}
int main(int argc, char* args[]) {
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
	SDL_Point points[3000];
	
	///=== create Event Timers ===
	auto triangleTimer = Skele_lib::SKGE::Counter();
	auto rectcounter = Skele_lib::SKGE::Counter();
	triangleTimer.setLeng(25);
	triangleTimer.setMax(100); 
	rectcounter.setLeng(10); 
	rectcounter.setMax(50); 
	///=== creating window ===
	int windw = 1920, windh = 1080;
	uint32_t wFlags = SDL_WINDOW_SHOWN, rFlags = SDL_RENDERER_ACCELERATED;
	auto window = Skele_lib::SKGE::Window("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windw, windh, wFlags, rFlags);

	
	///=== Set up the random number generator===
	int minr = 0, maxr = 100;
	int NUM_POINTS = 100;
	Skele_lib::SKGE::RNG rng;
	/// draw the frame
	bool drawFrame = true;
	bool showinv = false;
	///=== registering the keydown event===
	eQue.registerEvent("SDL_KEYDOWN",        { SDL_KEYDOWN, true }, [mil, mwl, mdl, mel,&window, &drawFrame, &showinv](const SDL_Event* e, Skele_lib::SKGE::World& world, size_t pid) {
		auto sym = e->key.keysym.sym;
		printf("SDL_KEDOWN EVENT PROC %c                               \n", sym);
		window.SetPuase(true);

		switch (sym) {
			case 'q': {
				drawFrame = !drawFrame; 
				break; 
			}
			case 'e': {
				showinv = !showinv; 
				break; 
			}
			default: {
				
				mil.Log("unhandled key %c press (0x%x)                    \n", sym, sym); 
				return;
			}

		}
	});
	eQue.registerEvent("TimerActiveTrigger", { 0, false }, [mil, mwl, mdl, mel, &window](const SDL_Event* e, Skele_lib::SKGE::World& world, size_t pid) {
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
	eQue.registerEvent("TimerTriggerReset", { 0, false }, [mil, mwl, mdl, mel, &window, &rectcounter, &eQue](const SDL_Event* e, Skele_lib::SKGE::World& world, size_t pid) {
		if (pid == 0) {
			window.RenderFilledCircle(16, 16, 16); 
			rectcounter(world, eQue); 
		}
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
			window.SetDrawColor(0, 0, 0);
			window.ClearScreenToDrawColor();
			window.SetDrawColor(255, 255, 0);
			if (!showinv) {
				for (size_t i = 0; i < NUM_POINTS; i++) {
					auto randomNumber = rng.GetNextNumberAsPercent(minr, maxr);
					float ty = ((float)windh * (((randomNumber * 2) - 1) / 2));
					int px = (int)(i * ((double)windw / NUM_POINTS));
					int py = ty + (windh / 2);
					points[i] = { px,py };
				}
			}
			window.RenderDrawLines(points, NUM_POINTS);
			if (showinv) {
				window.DrawInventory(9,5);
			}
			if (SDL_GetError()[0] != 0) {
				mel.Log("Frame %llu -> SDL_ERROR  %s", world.GetFrame(), SDL_GetError()); 
				exit(-1); 
			}
			triangleTimer(world,eQue);
			window.UpdateScreen();
			
		}
		world.DrawPlayers(window.renderer); 
		///===================================
		///=== DRAW THINGS           START ===
		/// 
		///=== DRAW THINGS             END ===
		///=== DRAW                    END ===
		///=== Increment the frame counter ===
		///===================================
		clearBuffer(u, 200, titlebuffer);
#ifdef _DEBUG
		
		sprintf_s(titlebuffer, "%s - %f fps [DEBUG] drawing %d showing invintory %d ","ENTER GAME TITLE HERE", 1.0 / world.dElapsedTime, drawFrame, showinv);

#elif
		sprintf_s(titlebuffer, "%s %s", "ENTER GAME TITLE HERE",  1.0 / world.dElapsedTime, drawFrame ? "" : "[paused]");
#endif // DEBUG
		window.SetWindowTitle(titlebuffer);
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
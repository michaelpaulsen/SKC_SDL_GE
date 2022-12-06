#pragma once
#include <SDL.h>
#include <string>
#include "EventHandler.h"
std::string GetWindowEventName(Uint8 wineventID) {
	switch (wineventID) {
	case SDL_WINDOWEVENT_FOCUS_GAINED:    return "window focus gained";
	case SDL_WINDOWEVENT_SHOWN:           return "window shown";
	case SDL_WINDOWEVENT_HIDDEN:          return "window hidden";
	case SDL_WINDOWEVENT_EXPOSED:         return "window exposed";
	case SDL_WINDOWEVENT_MOVED:           return "window moved";
	case SDL_WINDOWEVENT_RESIZED:         return "window resized";
	case SDL_WINDOWEVENT_SIZE_CHANGED:    return "window size changed ";
	case SDL_WINDOWEVENT_MINIMIZED:       return "window minimized";
	case SDL_WINDOWEVENT_MAXIMIZED:       return "window maximized";
	case SDL_WINDOWEVENT_RESTORED:        return "window restored";
	case SDL_WINDOWEVENT_ENTER:           return "window was entered";
	case SDL_WINDOWEVENT_LEAVE:           return "window was left";
	case SDL_WINDOWEVENT_FOCUS_LOST:      return "window focus lost";
	case SDL_WINDOWEVENT_CLOSE:           return "window closed";
	case SDL_WINDOWEVENT_TAKE_FOCUS:      return "window took focus";
	case SDL_WINDOWEVENT_HIT_TEST:        return "window hit test";
	case SDL_WINDOWEVENT_ICCPROF_CHANGED: return "window icc profile changed";
	case SDL_WINDOWEVENT_DISPLAY_CHANGED: return "window changed displays";
	default:                              return "Unknown / invalid window event id";

	}
}
double fdist(double x, double y) {
	return x * x + y * y; 
}
void registerDefaultEvents(EventQue &eq){
	static std::string inputTest; 
	eq.registerEvent("SDL_MOUSEMOTION", SDL_MOUSEMOTION, [](SDL_Event e) {
			if(fdist(e.motion.xrel,e.motion.yrel) >= 8){
				printf("moved the mouse to (%d,%d) [%d,%d]\n", e.motion.x, e.motion.y, e.motion.xrel,e.motion.yrel);
			}
		}
	);
	eq.registerEvent("SDL_WINDOWEVENT", SDL_WINDOWEVENT, [](SDL_Event e) {

			printf("%s\n", GetWindowEventName(e.window.event).c_str());
		}
	);
	eq.registerEvent("SDL_KEYDOWN", SDL_KEYDOWN, [](SDL_Event e) {
			if (!e.key.repeat) {
				printf("key %d (%c) pressed\n",e.key.keysym.scancode,e.key.keysym.sym);
			}
		}
	);
	eq.registerEvent("SDL_KEYUP", SDL_KEYUP, [](SDL_Event e) {
			if (!e.key.repeat) {
				printf("key %d (%c) released\n",e.key.keysym.scancode,e.key.keysym.sym);
			}
		}
	);
	eq.registerEvent("SDL_MOUSEBUTTONDOWN", SDL_MOUSEBUTTONDOWN, [](SDL_Event e) {
			printf("mouse button %d pressed\n", e.button.button);
		}
	); 
	eq.registerEvent("SDL_MOUSEBUTTONUP", SDL_MOUSEBUTTONUP, [](SDL_Event e) {
			printf("mouse button %d released\n", e.button.button);
		}
	);
	eq.registerEvent("SDL_TEXTEDITING", SDL_TEXTEDITING, [](SDL_Event e) {
			printf("entered a text editing event %s", e.edit.text); 
		}
	);
	eq.registerEvent("SDL_TEXTINPUT", SDL_TEXTINPUT, [](SDL_Event e) {
			
			inputTest += e.text.text;

			printf("entered a text intput event %s (%s - %llu) \n", e.text.text, inputTest.c_str(), 4-inputTest.size());
			if (inputTest.size() >= 4) {
				printf("  too many chars in buffer (%llu >= 4 ) clearing\n", inputTest.size());
				inputTest = "";
			}
		}
	);
}
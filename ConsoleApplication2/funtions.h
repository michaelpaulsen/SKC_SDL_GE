#pragma once
#include <SDL.h>
#include <string>
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
}
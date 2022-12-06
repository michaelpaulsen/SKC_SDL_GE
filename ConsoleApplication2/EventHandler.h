#pragma once
#include <string>
#include <functional>
#include <SDL.h>
struct EventHandler
{
	typedef std::function<void(SDL_Event)> CallBack_T;

	CallBack_T callback;
	std::string name;
	EventHandler(std::string n, CallBack_T callbackfunction) {
		callback = callbackfunction;
		name = n;
	}
	explicit EventHandler(CallBack_T callbackfunction) {
		callback = callbackfunction;
		name = "default";
	}
	void operator()(SDL_Event t) {
		this->callback(t);
	}
};

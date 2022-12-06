#pragma once
#include <string>
#include <vector>
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

class EventQue {
	std::vector<EventHandler> events;
public:
	void registerEvent(EventHandler hndl) {
		events.push_back(hndl);
		//this should not be used as it copyies the handle instead of making one in place. 
	}
	void registerEvent(std::string n, EventHandler::CallBack_T hndl) {
		events.emplace_back(n, hndl);
		//this constructs an handel in place this is the form of this function that should be used the most 
	}
	void registerEvent(EventHandler::CallBack_T hndl) {
		events.emplace_back(hndl);
		//this constructs an handel in place this is the form of this function that should be used the most 
	}
	void callEventByName(std::string name, SDL_Event t) {
		for (auto& i : this->events) {
			if (i.name == name) {
				i(t);
			}
		}
	}
};
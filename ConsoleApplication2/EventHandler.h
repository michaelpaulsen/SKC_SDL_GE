#pragma once
#include <string>
#include <vector>
#include <functional>
#include <SDL.h>
struct EventHandler
{
	typedef std::function<void(SDL_Event, long double)> CallBack_T;
	Uint32 EventTid;
	CallBack_T callback;
	std::string name;
	EventHandler(std::string n, Uint32 TID, CallBack_T callbackfunction) {
		callback = callbackfunction;
		name = n;
		EventTid = TID; 
	}
	explicit EventHandler(CallBack_T callbackfunction) {
		callback = callbackfunction;
		name = "default";
		EventTid = 0; 
	}
	void operator()(SDL_Event t, long double felapsedTime) {
		this->callback(t, felapsedTime);
	}
};

class EventQue {
	std::vector<EventHandler> events;
public:
	void registerEvent(EventHandler hndl) {
		events.push_back(hndl);
		//this should not be used as it copyies the handle instead of making one in place. 
	}
	void registerEvent(std::string n, Uint32 TID, EventHandler::CallBack_T hndl) {
		events.emplace_back(n, TID, hndl);
		//this constructs an handel in place this is the form of this function that should be used the most 
	}
	void registerEvent(EventHandler::CallBack_T hndl) {
		events.emplace_back(hndl);
		//this constructs an handel in place this is the form of this function that should be used the most 
	}
	[[deprecated("use callEventByTID as this can lead to undifined behavior")]]
	void callEventByName(std::string name, SDL_Event t, long double felapsedTime) {
		for (auto& i : this->events) {
			if (i.name == name) {
				i(t, felapsedTime);
			}
		}
	}
	void callEventByTID(Uint32 tid,  SDL_Event t, long double felapsedTime) {
		bool found = false; // at least one callback was called 
		for (auto& i : this->events) {
			if (i.EventTid == tid) {
				found = true; 
				i(t, felapsedTime);
			}
		}
		if (!found) {
			printf("unhandled type %d\n", t.type); 
		}
	}
};
#pragma once
#include <string>
#include <vector>
#include <functional>
#include <SDL.h>
#include "./world.h"
namespace Skele_lib {
	namespace SKGE {
		struct EventHandler
		{
			typedef std::function<void(SDL_Event, World&)> CallBack_T;
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
			void operator()(SDL_Event t, World w) {
				this->callback(t, w);
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
			void callEventByTID(Uint32 tid, SDL_Event t, World world) {
				bool found = false; // at least one callback was called 
				for (auto& i : this->events) {
					if (i.EventTid == tid) {
						found = true;
						i.callback(t, world);
					}
				}
				if (!found) {
					printf("unhandled type %d (0x%x)\n", t.type, t.type);
				}
			}
		};
	}
}
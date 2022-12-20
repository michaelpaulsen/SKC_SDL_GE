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
			typedef std::function<void(const SDL_Event*, World&, size_t pid)> CallBack_T;
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
			void operator()(const SDL_Event* t, World w, size_t pid) {
				this->callback(t, w,pid);
			}
		};

		class EventQue {
			std::vector<EventHandler> events;
		public:
			void registerEvent(EventHandler hndl) {
				events.push_back(hndl);
				//this should not be used as it copyies the handle instead of making one in place. 
			}
			void registerEvent(std::string n, Uint32 TID, EventHandler::CallBack_T hndl) {events.emplace_back(n, TID, hndl);}
			[[depercated("use registerEvent(std::string n, Uint32 TID, EventHandler::CallBack_T hndl) instead")]]
			void registerEvent(EventHandler::CallBack_T hndl) {
				events.emplace_back(hndl);
				//this constructs an handel in place this is the form of this function that should be used the most 
			}
			void callEventByTID(Uint32 tid, const SDL_Event* t, World world, size_t pid = -1) {
				bool found = false; // at least one callback was called 
				for (auto& i : this->events) {
					if (i.EventTid == tid) {
						found = true;
						i(t, world, pid);
					}
				}
				if (!found) {
					printf("unhandled type %d (0x%x)\n", t->type, t->type);
				}
			}
			void callEventByName(std::string name, SDL_Event* t, World world, size_t pid) {
				bool found = false; // at least one callback was called 
				for (auto& i : this->events) {
					if (i.name == name) {
						found = true;
						i.callback(t, world);
					}
				}
				if (!found) {
					printf("unhandled name %s\n", name.c_str());
				}
			}
		};
		void ColideWithWalls(int w, int h, EventQue& eque, World wrld) {
			for (size_t i = 0; i < wrld.GetPlayerCount(); i++) {
				auto& player = wrld.GetPlayerAt(i);
				auto& force = player.GetForce();
				auto rect = player.getPlayerRect();
				if (rect.x <= 0 && force.m_x < 0) { eque.callEventByName("P_hit_left_bound",NULL, wrld, i);}
				if (rect.x >= w - rect.w && force.m_x > 0) { eque.callEventByName("P_hit_right_bound", NULL, wrld, i); }
				if (rect.y <= 0 && force.m_y < 0) { eque.callEventByName("P_hit_top_bound", NULL, wrld, i);}
				if (rect.y >= h - rect.h && force.m_y > 0) { eque.callEventByName("P_hit_bottom_bound", NULL, wrld, i); }
			}
		}
	}
}
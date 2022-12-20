#pragma once 
#include <SDL.h>
namespace Skele_lib {
	namespace SKGE {
		class Event_t {
			uint32_t tid; 
			bool isSDLEvent; 
		public: 
			Event_t() {
				tid = 0; 
				isSDLEvent = false; 
			}
			Event_t(uint32_t id, bool t) {
				tid = id; 
				isSDLEvent = t; 
			}
			bool IsSDLEvent() {
				return isSDLEvent; 
			}
			uint32_t GetTid() {
				return tid; 
			}
			bool operator==(Event_t o) {
				return (tid == o.GetTid()) && (isSDLEvent == o.IsSDLEvent()); 
			}
		};
	}
}
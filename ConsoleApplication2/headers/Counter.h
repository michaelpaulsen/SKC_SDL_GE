#pragma once
#include "./EventHandler.h"
namespace Skele_lib {
	namespace SKGE {
		class Counter {
			size_t m_count = 0, m_max = 0xff, m_leng = 1, m_uid;
			 static size_t nutid;
		public:

			     Counter    () {
				m_uid = nutid++;
			}
			void IncCount   () {
				++m_count;
			}
			void setLeng    (size_t nleng) {
				m_leng = nleng;
			}
			void setMax     (size_t nleng) {
				m_max = nleng;
			}
			bool IsActive   () {
				return m_count <= m_leng;
			}
			void operator() (World w, EventQue eq) {
				if (m_count < m_leng) {
					eq.callEventByName("TimerActiveTrigger", NULL,  w, m_uid);
				}
				if (m_count == m_max) {
					eq.callEventByName("TimerTriggerReset", NULL, w, m_uid);
					m_count = 0;
				}else{
					++m_count;
				}
			}
		};
		size_t Counter::nutid = 0;
	}
}
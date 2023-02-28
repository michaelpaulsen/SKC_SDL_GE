#pragma once
#include <cstdarg> 
#include <iostream>
#include <fstream>
#include <format>

#include "Defines.h"
namespace Skele_lib {
	namespace SKGE {
		class LOGGER {
			CSTRING  m_name;
			//std::ostream out;
			//std::streambuf* buf;
			std::streambuf* buf;
			std::ofstream of;
			std::ostream *out; 
		public:
			LOGGER(cCSTRING  name) {
				m_name = name; 
				buf = std::cout.rdbuf();
				out = new std::ostream(buf);
			}
			LOGGER(cCSTRING  name, std::string filename) {
				m_name = name; 
				buf = std::cout.rdbuf();
				out = new std::ostream(buf);
			}
			LOGGER(LOGGER&) = delete; 
			LOGGER(LOGGER&&) = delete; 
			void Log(cCSTRING  message ) const {
				std::cout << std::format("[{}-LOG]{}", m_name, message);
			}
			void Print(cCSTRING  message) {
				std::cout << std::format("[{}]{}", m_name, message);
			}
			void Warn(cCSTRING  message) {
				std::cout << std::format("[{}-Warn]{}", m_name, message);
			}
			void Error(cCSTRING  message) {
				std::cout << std::format("[{}-Error]{}", m_name, message);
			}
			void operator()(cCSTRING message ) {
				Print(message); 
			}
		};
	}
}
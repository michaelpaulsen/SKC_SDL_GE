#pragma once
#include <cstdarg> 

#include "Defines.h"
namespace Skele_lib {
	namespace SKGE {
		class LOGGER {
			CSTRING  m_name;
			size_t VaLog(cCSTRING fmt, va_list args) {
				size_t leng = 0;
				leng += vprintf(fmt, args);
				return leng;
			}
		public:
			LOGGER(cCSTRING  name) {
				m_name = (CSTRING)malloc(strlen(name)+1);
				size_t i = 0; 
				while (name[i]) {
					m_name[i] = name[i]; 
					++i;
				}
				m_name[i] = 0; 
			}
			size_t Log(cCSTRING  fmt, ...) const {
				size_t leng = 0; 
				leng += printf("[%s] ", m_name); 
				va_list args;
				va_start(args, fmt);
				leng += vprintf(fmt, args); 
				va_end(args);
				return leng;
			}
			size_t Print(cCSTRING  fmt, ...) {
				size_t leng = 0;
				va_list args;
				va_start(args, fmt);
				leng += vprintf(fmt, args);
				va_end(args);
				return leng;
			}
			size_t PrintTo(const int endpos, const int startpos = 0) {
				size_t pos = startpos, retval = 0; 
				while (pos < endpos) {
					auto incval = printf(" "); 
					retval += incval; 
					pos += incval; 
				}
				return retval; 
			}
			size_t operator()(cCSTRING  fmt, ...) {
				size_t leng = printf("[%s] ", m_name);
				va_list va;
				va_start(va, fmt); 
				VaLog(fmt, va);
				va_end(va);
			}
		};
	}
}
#pragma once
#include <cstdarg> 

#ifndef c_str 
#define c_str char* 
#endif // !c_str 

namespace Skele_lib {
	namespace SKGE {
		class LOGGER {
			c_str m_name;
		public:
			LOGGER(const c_str name) {
				m_name = (c_str)malloc(strlen(name)+1);
				size_t i = 0; 
				while (name[i]) {
					m_name[i] = name[i]; 
					++i;
				}
				m_name[i++] = 0; 
			}
			size_t Log(const c_str fmt, ...) const {
				size_t leng = 0; 
				leng += printf("[%s] ", m_name); 
				va_list args;
				va_start(args, fmt);
				leng += vprintf(fmt, args); 
				va_end(args);
				return leng;
			}
			size_t Print(const c_str fmt, ...) {
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
		};
	}
}
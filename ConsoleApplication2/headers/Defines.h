#pragma once
#include <iostream>
#include <format>
#ifndef cerrf
#define cerrf  std::cerr << std::format
#endif
#ifndef coutf
#define coutf  std::cout << std::format
#endif

#ifndef CSTRING  
#define CSTRING  char* 
#endif // !CSTRING  
#ifndef cCSTRING  
#define cCSTRING  const char* 
#endif // !CSTRING  
#ifndef CBuffer  
#define CBuffer(name, size) char name[size] 
#endif
#ifndef clearBuffer
#define clearBuffer(s, size, buffer) for(size_t s = 0; s < size; s++){buffer[s] = 0;}
#endif
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

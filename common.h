#pragma once

#include <cstdint>
#include <iostream>

#ifndef NDEBUG
	#define COUT(s) std::cout << s
#else
	#define COUT(s)
#endif


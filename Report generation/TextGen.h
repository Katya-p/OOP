#ifndef __textgen_h 
#define __textgen_h 
#include "SimpleGen.h"

struct TextGen {
	const struct SimpleGen _;
	FILE* file_out;
};

extern const void *TextGen;

#endif
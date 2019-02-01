#ifndef __simplegen_h 
#define __simplegen_h 

struct SimpleGen {
	const void *class;
	size_t recs_on_page;
	FILE* file_in;
};

extern const void *SimpleGen;

#endif
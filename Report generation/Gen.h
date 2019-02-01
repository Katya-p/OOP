#ifndef __gen_h 
#define __gen_h 

#include <stddef.h> 
#include <stdarg.h> 
#include <stdio.h> 
#define N 500

struct Class {
	size_t size;
	void *(*ctor)(void *self, va_list *app); 
	void *(*dtor)(void *self); 
    void(*generator)(void *self);
	void(*record)(const void *self, char* rec, int flag);
	void(*separator)(const void *self);
	void(*uheader)(const void *self, int page);
	void(*dheader)(const void *self, int page);
};
//not virtual
void *new(const void *_class, ...);
void delete(void *item);
void parsing(char *str, char *str1, char *str2);
//virtual
void generator(void *self);
void record(const void *self, char* rec, int flag);
void separator(const void *self);
void uheader(const void *self, int page);
void dheader(const void *self, int page);

#endif
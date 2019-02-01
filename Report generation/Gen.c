//#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h> 
#include <string.h>
#include <assert.h> 
#include "Gen.h" 

void *new(const void *_class, ...){
	const struct Class *class = _class;
	void *p = calloc(1, class->size);
	assert(p);
	*(const struct Class **)p = class;
	if (class->ctor) {
		va_list ap;
		va_start(ap, _class);
		p = class->ctor(p, &ap);
		va_end(ap);
	}	
	return p;
}

void delete(void *self)
{
	const struct Class **cp = self;
	if (self && *cp && (*cp)->dtor){ 
		self = (*cp)->dtor(self); 
	} 
	free(self);
}

void record(const void *self, char* rec, int flag)
{
	const struct Class * const *cp = self;
	assert(self && *cp && (*cp)->record);
	(*cp)->record(self, rec, flag);
}

void separator(const void *self)
{
	const struct Class * const *cp = self;
	assert(self && *cp && (*cp)->separator);
	(*cp)->separator(self);
}

void uheader(const void *self, int page)
{
	const struct Class * const *cp = self;
	assert(self && *cp && (*cp)->uheader);
	(*cp)->uheader(self, page);
}

void dheader(const void *self, int page)
{
	const struct Class * const *cp = self;
	assert(self && *cp && (*cp)->dheader);
	(*cp)->dheader(self, page);
}

void parsing(char *str, char *str1, char *str2){
    size_t size = strlen(str);
    int flag = 0;
    int place = 0;
    for (size_t i = 0; i < size; i++){
        char c = *(str + i);

        if ((c == ' ') && (flag == 0)){
            flag = 1;
            place = i + 3;
            *(str1 + i) = '\0';
            continue;
        }
        if (flag == 0){
            *(str1 + i) = c;
        }
        else if (flag == 1){
            if ((c == ' ') || (c == ':')){
                continue;
            }
            *(str2 + i - place) = c;
        }
    }
    if (*(str2 + size - place - 1) == '\n'){
        *(str2 + size - place - 1) = '\0';
    }
}

void generator(void *self){
    const struct Class * const *cp = self;
    assert(self && *cp && (*cp)->generator);
    (*cp)->generator(self);
}
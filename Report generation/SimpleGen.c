#include <stdarg.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include <assert.h>
#include "SimpleGen.h" 
#include "Gen.h" 

static void *simple_ctor(void *_self, va_list *app)
{
	struct SimpleGen *self = _self;
	self->recs_on_page = va_arg(*app, size_t);
	self->file_in = va_arg(*app, FILE*);
	return self;
}

static void simple_record(const void *_self, char* rec, int flag)
{
	const struct SimpleGen *self = _self;
	printf("%s", rec);
	if (flag == 1){
		printf("%c", '\n');
	}
}

static void simple_separator(const void *_self)
{
	const struct SimpleGen *self = _self;
	printf("%c", ' '); 
}

static void simple_uheader(const void *_self, int page)
{
	const struct SimpleGen *self = _self;
	printf("%c", '\n');
}

static void simple_dheader(const void *_self, int page)
{
	const struct SimpleGen *self = _self;
	printf("%c", '\n');
}

void simple_generator(void* self){
    //const struct Class **cp = self;
    size_t recs_on_page;
    FILE *file;
    struct SimpleGen *selfp = self;
    recs_on_page = selfp->recs_on_page;
    file = selfp->file_in;

    int count = 0;
    int page = 1;
    int amount_of_recs = 0;
    simple_uheader(self, page);
    assert(recs_on_page != 0);
    for (;;){
        char str[N] = { 0 };
        char str1[N] = { 0 };
        char str2[N] = { 0 };
        char* res = fgets(str, N, file);
        if (res == NULL){
            break;
        }
        else if (*res == '\n'){
            continue;
        }
        else {
            if ((count % recs_on_page == 0) && (count != 0)){
                simple_uheader(self, page);
            }
            parsing(str, str1, str2);
            simple_record(self, str1, 0);
            simple_separator(self);
            simple_record(self, str2, 1);
            count++;
            if (count % recs_on_page == 0){
                page++;
                simple_dheader(self, page);
            }
        }
    }
    if (count % recs_on_page != 0){
        simple_dheader(self, page + 1);
    }
}

static const struct Class _SimpleGen = {
	sizeof(struct SimpleGen),
	simple_ctor,
	0,
    simple_generator,
	simple_record,
	simple_separator,
	simple_uheader,
	simple_dheader
};

const void *SimpleGen = &_SimpleGen;
#include <stdarg.h> 
#include <stdlib.h> 
#include <string.h>
#include <stdio.h> 
#include <assert.h>
#include "TextGen.h" 
#include "SimpleGen.h"
#include "Gen.h"


void text_get_recs_file(void *self, size_t *recs_on_page_p, FILE** file_p){
	struct SimpleGen *selfp = self;
	*recs_on_page_p = selfp->recs_on_page;
	*file_p = selfp->file_in;
}

static void *text_ctor(void *_self, va_list *app)
{
	struct TextGen *self = ((const struct Class *)SimpleGen)->ctor(_self, app);
	self->file_out = va_arg(*app, FILE*);
	return self;
}

static void text_record(const void *_self, char* rec, int flag)
{
	const struct TextGen *self = _self;
	if (flag == 1){
		for (size_t i = 0; i < strlen(rec); i++){
			if ((*(rec + i) <= 90) && (*(rec + i) >= 65)) { *(rec + i) += 32; }
		}
	}
	else {
		for (size_t i = 0; i < strlen(rec); i++){
			if ((*(rec + i) <= 122) && (*(rec + i) >= 97)) { *(rec + i) -= 32; }
		}
	}
	fputs(rec, self->file_out);
	if (flag == 1){
		fputs("\n", self->file_out);
	}
}

static void text_separator(const void *_self)
{
	const struct TextGen *self = _self;
	fputs(" ", self->file_out);
}

static void text_uheader(const void *_self, int page)
{
	const struct TextGen *self = _self;
	fprintf(self->file_out, "%d\n", page);
}

static void text_dheader(const void *_self, int page)
{
	const struct TextGen *self = _self;
	fprintf(self->file_out, "%d\n", page - 1);
}

void text_generator(void* self){
    //const struct Class **cp = self;

    size_t recs_on_page;
    FILE *file;
    struct SimpleGen *selfp = self;
    recs_on_page = selfp->recs_on_page;
    file = selfp->file_in;

    int count = 0;
    int page = 1;
    int amount_of_recs = 0;
    text_uheader(self, page);
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
                text_uheader(self, page);
            }
            parsing(str, str1, str2);
            text_record(self, str1, 0);
            text_separator(self);
            text_record(self, str2, 1);
            count++;
            if (count % recs_on_page == 0){
                page++;
                text_dheader(self, page);
            }
        }
    }
    if (count % recs_on_page != 0){
        text_dheader(self, page + 1);
    }
}


static const struct Class _TextGen = {
	sizeof(struct TextGen),
	text_ctor,
	0,
    text_generator,
	text_record,
	text_separator,
	text_uheader,
	text_dheader	
};

const void *TextGen = &_TextGen;


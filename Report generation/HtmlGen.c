#include <stdarg.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "TextGen.h" 
#include "HtmlGen.h"
#include "SimpleGen.h"
#include "Gen.h"

static void file_begin(FILE* file){
    fputs("<!DOCTYPE html>\n", file);
    fputs("<html>\n", file);
    fputs("<head>\n", file);
    fputs("<meta charset = \"utf - 8\">\n", file);
    fputs("<title>Output</title>\n", file);
    fputs("</head>", file);
    fputs("<body bgcolor=\"MidnightBlue\">\n", file);
}

static void file_end(FILE* file){
    fputs("</body>\n", file);
    fputs("</html>\n", file);
}

static void html_get_recs_file(void *self, size_t *recs_on_page_p, FILE** file_p){
    struct SimpleGen *selfp = self;
    *recs_on_page_p = selfp->recs_on_page;
    *file_p = selfp->file_in;
}

static void *html_ctor(void *_self, va_list *app)
{
    struct HtmlGen *self = ((const struct Class *)TextGen)->ctor(_self, app);
    return self;
}

static void html_record(const void *_self, char* rec, int flag)
{
    const struct TextGen *self = _self;
    if (flag == 1){
        for (size_t i = 0; i < strlen(rec); i++){
            if ((*(rec + i) <= 90) && (*(rec + i) >= 65)) { *(rec + i) += 32; }
        }
        fputs("<big><font color=\"DeepSkyBlue\"><i>", self->file_out);
        fputs(rec, self->file_out);
        fputs("</i></p></font></big>\n", self->file_out);

    }
    else {
        for (size_t i = 0; i < strlen(rec); i++){
            if ((*(rec + i) <= 122) && (*(rec + i) >= 97)) { *(rec + i) -= 32; }
        }
        fputs("<big><font color=\"Cornsilk\"><p align=\"center\"><b>", self->file_out);
        fputs(rec, self->file_out);
        fputs("</b></font></big>", self->file_out);
    }
}

static void html_separator(const void *_self)
{
    const struct TextGen *self = _self;
    fputs(" ", self->file_out);
}

static void html_uheader(const void *_self, int page)
{
    const struct TextGen *self = _self;
    fputs("<p></p>\n", self->file_out);
}

static void html_dheader(const void *_self, int page)
{
    const struct TextGen *self = _self;
    fputs("<font color=\"Khaki\"><p align=\"right\"><small>", self->file_out);
    fprintf(self->file_out, "%d", page - 1);
    fputs("</small></p></font>\n", self->file_out);
}

void html_generator(void* self){
    size_t recs_on_page;
    FILE *file;
    struct SimpleGen *selfp = self;
    recs_on_page = selfp->recs_on_page;
    file = selfp->file_in;
    
    struct TextGen *selfp1 = self;
    FILE *fileOut = selfp1->file_out;

    file_begin(fileOut);
    int count = 0;
    int page = 1;
    int amount_of_recs = 0;
    html_uheader(self, page);
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
                html_uheader(self, page);
            }
            parsing(str, str1, str2);
            html_record(self, str1, 0);
            html_separator(self);
            html_record(self, str2, 1);
            count++;
            if (count % recs_on_page == 0){
                page++;
                html_dheader(self, page);
            }
        }
    }
    if (count % recs_on_page != 0){
        html_dheader(self, page + 1);
    }
    file_end(file);
}

static const struct Class _HtmlGen = {
    sizeof(struct HtmlGen),
    html_ctor,
    0,
    html_generator,
    html_record,
    html_separator,
    html_uheader,
    html_dheader
};

const void *HtmlGen = &_HtmlGen;

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h> 
#include "Gen.h" 
#include "SimpleGen.h" 
#include "TextGen.h"
#include "HtmlGen.h"
#include <errno.h>

void main(){
    
	FILE *inh;
	errno_t errinh;
	errinh = fopen_s(&inh, "input.txt", "r");
	assert(errinh == 0);
    FILE *outh;
    errno_t errouth;
    errouth = fopen_s(&outh, "output.html", "w");
    assert(errouth == 0);
	void* ph = new(HtmlGen, 5, inh, outh);
	//file_begin(outh);
	generator(ph);
	//file_end(outh);
	delete(ph);
	fclose(inh);
	fclose(outh);
    
    FILE *ins;
    errno_t errins;
    errins = fopen_s(&ins, "input.txt", "r");
    assert(errins == 0);
    void* ps = new(SimpleGen, 5, ins);
    generator(ps);
    delete(ps);
    fclose(ins);
    
    FILE *inf1;
    errno_t errinf1;
    errinf1 = fopen_s(&inf1, "input.txt", "r");
    assert(errinf1 == 0);
    FILE *outf1;
    errno_t erroutf1 = fopen_s(&outf1, "output1.txt", "w");
    assert(erroutf1 == 0);
    void* p1 = new(TextGen, 5, inf1, outf1);
    generator(p1);
    delete(p1);
    fclose(inf1);
    fclose(outf1);

    FILE *inf2;
    errno_t errinf2;
    errinf2 = fopen_s(&inf2, "input.txt", "r");
    assert(errinf2 == 0);
    FILE *outf2;
    errno_t erroutf2 = fopen_s(&outf2, "output2.txt", "w");
    assert(erroutf2 == 0);
    void* p2 = new(TextGen, 2, inf2, outf2);
    generator(p2);
    delete(p2);
    fclose(inf2);
    fclose(outf2);
    
	_CrtDumpMemoryLeaks();
}

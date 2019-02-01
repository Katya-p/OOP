#include <stdio.h> 
#include <stdlib.h> 
#include "Array.h" 

struct _RecordArray {
    void* records;
    size_t record_size;
    size_t size;
};

RecordArray *ra_create(size_t size, size_t record_size){
    if (record_size == 0){
        return NULL;
    }
    RecordArray *res = (RecordArray*)malloc(sizeof(RecordArray));
    void *mass = malloc(record_size * size);
    if ((mass == NULL) || (res == NULL)){
        free(res);
        free(mass);
        return NULL;
    }
    res->records = mass;
    res->record_size = record_size;
    res->size = size;
    return res;
}

void *ra_get(RecordArray *arr, size_t idx){
    if ((arr != NULL) && (arr->size != 0) && (idx >= 0) && (idx < arr->size)){
        return (char*)(arr->records) + idx * arr->record_size;
    }
    return NULL;
}

void ra_set(RecordArray *arr, size_t idx, void *record){
    if (ra_get(arr, idx) != NULL){
        for (int i = 0; i < arr->record_size; i++){
            *((char*)(arr->records) + idx * arr->record_size + i) = *((char*)record + i);
        }
    }
}

void ra_delete(RecordArray *arr){
    free(arr->records);
    free(arr);
}
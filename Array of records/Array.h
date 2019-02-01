#ifndef ARRAY_H 
#define ARRAY_H 

struct _RecordArray;
typedef struct _RecordArray RecordArray;

RecordArray *ra_create(size_t size, size_t record_size);
void ra_delete(RecordArray *arr);
void *ra_get(RecordArray *arr, size_t idx);
void ra_set(RecordArray *arr, size_t idx, void *record);

#endif
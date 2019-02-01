#ifndef IMAGEFIFO
#define IMAGEFIFO

#include "ImageFifo.h"
#include <mutex>
#include <algorithm>
#include <vector>

struct ImageFIFO {
	ImageFIFO(size_t blockSize, size_t maxBlocks);
	~ImageFIFO();
	void * getFree();
	void addReady(void * data);
	void * getReady();
	void addFree(void * data);
private:
	ImageFIFO(ImageFIFO const &);
	ImageFIFO& operator=(ImageFIFO const &) {}
	size_t blockSize;
	size_t maxBlocks;
	int ready_offset;
	int free_offset;
	std::vector<char*> blocks;
	bool empty;
	std::mutex mutex;
};

#endif
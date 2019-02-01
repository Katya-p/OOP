#include "ImageFifo.h"

ImageFIFO::ImageFIFO(size_t blockSize, size_t maxBlocks)
	:blockSize(blockSize), maxBlocks(maxBlocks), ready_offset(0), free_offset(0), blocks(maxBlocks), empty(true)
{
	for (size_t i = 0; i < maxBlocks; i++) {
		blocks[i] = new char[blockSize];
	}
}

ImageFIFO::~ImageFIFO() {
	for (size_t i = 0; i < maxBlocks; i++) {
		delete[] blocks[i];
	}
}

void * ImageFIFO::getFree() {
	std::lock_guard<std::mutex> lock(mutex);
	if (!empty) {
		return nullptr;
	}
	return blocks[free_offset];
}

void ImageFIFO::addReady(void * data) {
	std::lock_guard<std::mutex> lock(mutex);
	free_offset++;
	if (free_offset == maxBlocks) {
		free_offset = 0;
	}	

	if (free_offset == ready_offset) {
		empty = false;
	}
}

void * ImageFIFO::getReady() {
	std::lock_guard<std::mutex> lock(mutex);
	if (empty) {
		return nullptr;
	}
	return blocks[ready_offset];
}

void ImageFIFO::addFree(void * data) {
	std::lock_guard<std::mutex> lock(mutex);
	std::vector<char*>::iterator it = std::find(blocks.begin(), blocks.end(), data);
	**it = '\0';
	ready_offset++;
	if (ready_offset == maxBlocks) {
		ready_offset = 0;
	}
	if (free_offset == ready_offset) {
		empty = true;
	}
}


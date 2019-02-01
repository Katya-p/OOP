#include "pch.h"
#include "../ImageQueue/ImageFifo.h"
void reader(ImageFIFO & fifo, const std::vector<char*> & strings, size_t blockSize) {
	for (auto it : strings) {
		void* data = fifo.getFree();
		if (data != nullptr) {
			for (size_t i = 0; i < blockSize; i++) {
				*((char*)data + i) = it[i];
			}
			fifo.addReady(data);
		}
	}
}
void writer(ImageFIFO & fifo, std::vector<char*> & res_strings, size_t blockSize) {
	for (auto it : res_strings) {
		void* data = fifo.getReady();
		if (data != nullptr) {
			for (size_t i = 0; i < blockSize; i++) {
				it[i] = *((char*)data + i);
			}
			fifo.addFree(data);
		}
	}
}

TEST(TestCase, OneThread) {
	size_t amount_of_strings = 10;
	size_t blockSize = sizeof(char) * 3;
	std::vector<char*> strings(amount_of_strings);
	for (size_t i = 0; i < amount_of_strings; i++) {
		strings[i] = new char[blockSize];
	}
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (auto it : strings) {
		for (size_t i = 0; i < blockSize - 1; ++i) {
			it[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		it[blockSize - 1] = '\0';
	}

	std::vector<char*> res_strings(amount_of_strings);
	for (size_t i = 0; i < amount_of_strings; i++) {
		res_strings[i] = new char[blockSize];
	}
	ImageFIFO fifo(blockSize, amount_of_strings);
	reader(fifo, strings, blockSize);
	writer(fifo, res_strings, blockSize);


	for (size_t i = 0; i < amount_of_strings; i++) {
		for (size_t j = 0; j < blockSize; j++) {
			ASSERT_EQ(strings[i][j], res_strings[i][j]);
		}
	}

	for (size_t i = 0; i < amount_of_strings; i++) {
		delete[] strings[i];
		delete[] res_strings[i];
	}
}

TEST(TestCase, TwoThreads) {
	size_t amount_of_strings = 10;
	size_t blockSize = sizeof(char) * 3;
	std::vector<char*> strings(amount_of_strings);
	for (size_t i = 0; i < amount_of_strings; i++) {
		strings[i] = new char[blockSize];
	}
	static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (auto it : strings) {
		for (size_t i = 0; i < blockSize - 1; ++i) {
			it[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		}
		it[blockSize - 1] = '\0';
	}

	std::vector<char*> res_strings(amount_of_strings);
	for (size_t i = 0; i < amount_of_strings; i++) {
		res_strings[i] = new char[blockSize];
	}
	ImageFIFO fifo(blockSize, amount_of_strings);
	std::thread treadReader(reader, std::ref(fifo), std::ref(strings), blockSize);
	std::thread treadWriter(writer, std::ref(fifo), std::ref(res_strings), blockSize);
	treadReader.join();
	treadWriter.join();

	for (size_t i = 0; i < amount_of_strings; i++) {
		for (size_t j = 0; j < blockSize; j++) {
			ASSERT_EQ(strings[i][j], res_strings[i][j]);
		}
	}

	for (size_t i = 0; i < amount_of_strings; i++) {
		delete[] strings[i];
		delete[] res_strings[i];
	}
}

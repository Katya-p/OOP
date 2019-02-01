#ifndef POLICY
#define POLICY
#include <unordered_map>
#include <time.h>

template <typename K>
class NeverDelete {
public:
	bool operator()(const K & key) {
		return false;
	}
};

template <typename K, size_t NUM >
class SpecifiedNumberOfHits {
	std::unordered_map<K, size_t> counters; //счетчики количества обращений для каждого элемента таблицы
public:
	bool operator()(const K & key) {
		if (counters.find(key) != counters.end()) {
			counters.at(key)++;
		}
		else {
			counters.insert({key, 1});
		}
		if (counters.at(key) == NUM + 1) {
			return true;
		}
		return false;
	}
};

template <typename K, time_t TIME >
class SpecifiedTime {
	std::unordered_map<K, time_t> timers;//счетчики времени для каждого элемента таблицы
public:
	using iterator = typename std::unordered_map<K, time_t>::iterator;
	bool operator()(const K & key) {
		iterator search = timers.find(key);
		if (search == timers.end()) {
			timers.insert({ key, time(NULL) });
			return false;
		}
		if (time(NULL) - timers[key] >= TIME) {
			return true;
		}
		return false;
	}
};

#endif

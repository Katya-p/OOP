#ifndef HASHTABLE
#define HASHTABLE
#include "DeletionPolicy.h"
#include <type_traits>
#include <utility>
template <typename K, typename V, typename Policy>
class HashTable {
	using iterator = typename std::unordered_map<K, V>::iterator;
	std::unordered_map<K, V> map;
	Policy policy;
	iterator current_elem;
public:
	void insert(K key, V value) {
		map.insert({ key, value });
	}

	iterator find(const K & key) {
		iterator tmp = map.find(key);
		if (tmp == map.end()) {
			return current_elem;
		}
		current_elem = tmp;
		if (policy(key)) {
			erase(current_elem);
		}
		return current_elem;
	}

	V & at(const K& key) {
		iterator tmp = map.find(key);
		if (tmp == map.end()) {
			return current_elem->second;
		}
		current_elem = tmp;
		if (policy(key)) {
			return erase(current_elem)->second;
		}
		return map.at(key);
	}

	V& operator[](const K& key) {
		current_elem = map.find(key);
		if ((current_elem != map.end()) && policy(key)) {
			return erase(current_elem)->second;
		}
		return map[key];
	}

	iterator erase(iterator pos) {
		current_elem++;
		map.erase(pos);
		return current_elem;
	}
	
	iterator begin() {
		current_elem = map.begin();
		return current_elem;
	}
	iterator end() {
		current_elem = map.end();
		return current_elem;
	}	

	template< class... Args >
	std::pair<iterator, bool> emplace(Args&&... args) {
		return map.emplace(std::forward<Args>(args)...);
	}

	template <class... Args>
	std::pair<iterator, bool> try_emplace(const K & k, Args&&... args) {
		return map.try_emplace(k, std::forward<Args>(args)...);
	}
};

#endif
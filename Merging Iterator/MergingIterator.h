#ifndef MITERATOR_H
#define MITERATOR_H

#include <vector>
#include <initializer_list>
#include <utility>
#include <type_traits>
#include <algorithm>
template <bool is_less = true>
struct ComparisonMode {
	template <typename T>
	static bool compare(T a, T b) {
		return a < b;
	}
};
template <>
struct ComparisonMode<false> {
	template <typename T>
	static bool compare(T a, T b) {
		return a > b;
	}
};

template <typename IT, typename ComparisonPolicy = ComparisonMode<true> >
class MergingIterator
{
	IT it;
	std::vector<IT> first_iterators;
	std::vector<IT> last_iterators;
public:
	MergingIterator()
	{}

	MergingIterator(std::initializer_list< std::pair<IT, IT> > list)
	{
		for (auto elem : list) {
			first_iterators.push_back(elem.first);
			last_iterators.push_back(elem.second);
		}
		IT minimum = first_iterators.at(0);
		size_t index = 0;
		for (size_t i = 1; i < first_iterators.size(); i++) {
			if (ComparisonPolicy::compare(*first_iterators.at(i), *minimum)) {
				minimum = first_iterators.at(i);
				index = i;
			}
		}
		it = minimum;
		/*it = std::min_element(first_iterators.begin(), first_iterators.end(), ComparisonPolicy::compare);
		size_t index = std::distance(first_iterators.begin(), it);*/
		++first_iterators.at(index);
		if (first_iterators.at(index) == last_iterators.at(index)) {
			first_iterators.erase(first_iterators.begin() + index);
			last_iterators.erase(last_iterators.begin() + index);
		}
	}

	typedef typename std::iterator_traits<IT>::value_type value_type;
	value_type operator*() const {
		return *it;
	}

	bool operator!=(const MergingIterator<IT, ComparisonPolicy> &other) const {
		
		return  (first_iterators != other.first_iterators) || (last_iterators != other.last_iterators);
	}
	bool operator==(const MergingIterator<IT, ComparisonPolicy> &other) const {
		return !(*this != other);
	}

	MergingIterator<IT, ComparisonPolicy> & operator++() {
		if (first_iterators.size() != 0) {
			IT minimum = first_iterators.at(0);
			size_t index = 0;
			for (size_t i = 1; i < first_iterators.size(); i++) {
				if (ComparisonPolicy::compare(*first_iterators.at(i), *minimum)) {
					minimum = first_iterators.at(i);
					index = i;
				}
			}
			it = first_iterators.at(index);
			++first_iterators.at(index);

			if (first_iterators.at(index) == last_iterators.at(index)) {
				first_iterators.erase(first_iterators.begin() + index);
				last_iterators.erase(last_iterators.begin() + index);
			}
		}
		return *this;
	}

	MergingIterator<IT, ComparisonPolicy> operator++(int)
	{
		MergingIterator<IT, ComparisonPolicy> tmp(*this);
		++(*this);
		return tmp;
	}
};

namespace std {
	template <typename C>
	struct iterator_traits<MergingIterator<C> > {
		using iterator_category = std::forward_iterator_tag;
		using value_type = typename std::iterator_traits<C>::value_type;
	};
}


#endif


#ifndef MRANGES_H
#define MRANGES_H

#include "MergingIterator.h"

template <typename IT, typename ComparisonPolicy = ComparisonMode<true> >
class MergeRanges {
	MergingIterator<IT, ComparisonPolicy> iterator;
	MergingIterator<IT, ComparisonPolicy> iterator_begin;
	MergingIterator<IT, ComparisonPolicy> iterator_end;

public:

	MergeRanges<IT, ComparisonPolicy>(std::initializer_list< std::pair<IT, IT> > list)
		: iterator(MergingIterator<IT, ComparisonPolicy>(list)), iterator_begin(iterator), iterator_end(MergingIterator<IT, ComparisonPolicy>())
	{}

	MergingIterator<IT, ComparisonPolicy> begin() {
		return iterator_begin;
	}

	MergingIterator<IT, ComparisonPolicy> end() {
		return iterator_end;
	}	

};


#endif
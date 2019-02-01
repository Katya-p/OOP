#include "pch.h"
#include "../MergingIterator2/MergeRanges.h"
#include "../MergingIterator2/MergingIterator.h"
#include <forward_list>

TEST(TestCaseName, Test1) {
	std::vector<int> a = { 1, 3, 10 };
	std::vector<int> b = { 4, 6, 20 };
	std::vector<int> expected = { 1, 3, 4, 6, 10, 20 };
	MergeRanges<std::vector<int>::iterator> iter = { {a.begin(), a.end()}, {b.begin(), b.end() } };
	MergingIterator<std::vector<int>::iterator> begin = iter.begin();
	MergingIterator<std::vector<int>::iterator> end = iter.end();
	size_t i = 0;
	while (begin != end) {
		EXPECT_EQ(*begin, expected.at(i));
		i++;
		begin++;
	}
}

TEST(TestCaseName, Test2) {
	std::forward_list<int> a = { 2, 3, 10 };
	std::forward_list<int> b = { 4, 9, 20 };
	std::forward_list<int> expected = { 2, 3, 4, 9, 10, 20 };
	MergeRanges<std::forward_list<int>::iterator> iter = { {a.begin(), a.end()}, {b.begin(), b.end() } };
	MergingIterator<std::forward_list<int>::iterator> begin = iter.begin();
	MergingIterator<std::forward_list<int>::iterator> end = iter.end();
	size_t i = 0;
	while (begin != end) {
		EXPECT_EQ(*begin, expected.front());
		expected.pop_front();
		i++;
		begin++;
	}
}

TEST(TestCaseName, Test3) {
	std::vector<int> a = { 6, 3, 2, 1 };
	std::vector<int> b = { 30, 20, 10, 9, 5 };
	std::vector<int> c = { 90, 7 };
	std::vector<int> expected = { 90, 30, 20, 10, 9, 7, 6, 5, 3, 2, 1 };
	MergeRanges<std::vector<int>::iterator, ComparisonMode<false> > iter = { {a.begin(), a.end()}, {b.begin(), b.end() }, {c.begin(), c.end() } };
	MergingIterator<std::vector<int>::iterator, ComparisonMode<false>> begin = iter.begin();
	MergingIterator<std::vector<int>::iterator, ComparisonMode<false>> end = iter.end();
	size_t i = 0;
	while (begin != end) {
		EXPECT_EQ(*begin, expected.at(i));
		i++;
		begin++;
	}
}

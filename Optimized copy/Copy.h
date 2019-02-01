#ifndef COPY_H
#define COPY_H

#include <type_traits>
#include <iterator>    

template <class Iterator>
typename std::enable_if<std::is_fundamental<typename std::iterator_traits<Iterator>::value_type>::value && std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value, Iterator>::type
optimized_copy(Iterator first, Iterator last, Iterator result)
{
	size_t count = std::distance(first, last);
	memmove(&(*result), &(*first), count * sizeof(typename std::iterator_traits<Iterator>::value_type));
	return result;
}

template <class Iterator>
typename std::enable_if<!std::is_fundamental<typename std::iterator_traits<Iterator>::value_type>::value || !std::is_same<typename std::iterator_traits<Iterator>::iterator_category, std::random_access_iterator_tag>::value, Iterator>::type
optimized_copy(Iterator first, Iterator last, Iterator result)
{
	while (first != last) {
		*result = *first;
		++result;
		++first;
	}
	return result;
}

#endif

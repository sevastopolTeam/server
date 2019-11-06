#pragma once

#include <algorithm>

struct NAlgorithm {
    template<class Container>
    static void Sort(Container& container) {
		std::sort(container.begin(), container.end());
	}

    template <class RandomAccessIterator>
    static void Sort(RandomAccessIterator first, RandomAccessIterator last) {
        std::sort(first, last);
	}

    template <class RandomAccessIterator, class Compare>
    static void Sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        std::sort(first, last, comp);
	}
};

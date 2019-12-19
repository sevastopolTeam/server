#include "algorithm.h"
#include <algorithm>

namespace NAlgorithm {
    template<class Container>
    void Sort(Container& container) {
        std::sort(container.begin(), container.end());
    }

    template <class RandomAccessIterator>
    void Sort(RandomAccessIterator first, RandomAccessIterator last) {
        std::sort(first, last);
    }

    template <class RandomAccessIterator, class Compare>
    void Sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        std::sort(first, last, comp);
    }
};

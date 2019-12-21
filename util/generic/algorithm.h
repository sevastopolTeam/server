#pragma once

namespace NAlgorithm {
    template<class Container>
    void Sort(Container& container);

    template <class RandomAccessIterator>
    void Sort(RandomAccessIterator first, RandomAccessIterator last);

    template <class RandomAccessIterator, class Compare>
    void Sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp);
}

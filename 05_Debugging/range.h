#ifndef RANGE_H_
#define RANGE_H_

#include <iterator>

class Range;

class ForwardIteratorRange
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = int;
    using pointer = const int*;
    using reference = const int&;

    friend class Range;

    ForwardIteratorRange() : range_ptr_(nullptr) {}

    ForwardIteratorRange& operator++();
    ForwardIteratorRange operator++(int);
    bool operator==(const ForwardIteratorRange&) const noexcept;
    bool operator!=(const ForwardIteratorRange&) const noexcept;
    value_type operator*() const noexcept;

private:
    const Range* range_ptr_;
    size_t index_;

    ForwardIteratorRange(const Range* r_ptr, size_t i = 0) : range_ptr_(r_ptr), index_(i) {}
};

class Range
{
public:
    using const_iterator = ForwardIteratorRange;
    Range() = default;
    explicit Range(int stop);
    Range(int start, int stop, int step = 1);
    Range(const Range& other) = default;
    Range(Range&&) = default;

    Range& operator=(const Range& other) = default;
    Range& operator=(Range&&) = default;

    int operator[](size_t index) const noexcept;

    size_t size() const noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    ~Range() = default;

private:
    int start_ = 0;
    int stop_ = 0;
    int step_ = 1;
};

#endif // RANGE_H_

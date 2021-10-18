#include "range.h"

ForwardIteratorRange& ForwardIteratorRange::operator++()
{
    ++index_;

    return *this;
}

ForwardIteratorRange ForwardIteratorRange::operator++(int)
{
    ForwardIteratorRange ret_iterator(range_ptr_, index_);
    ++index_;

    return ret_iterator;
}

bool ForwardIteratorRange::operator==(const ForwardIteratorRange& other) const noexcept
{
    return index_ == other.index_;
}

bool ForwardIteratorRange::operator!=(const ForwardIteratorRange& other) const noexcept
{
    return index_ != other.index_;
}

ForwardIteratorRange::value_type ForwardIteratorRange::operator*() const noexcept
{
    return range_ptr_->operator[](index_);
}

Range::Range(int start, int stop, int step) : start_(start), stop_(stop), step_(step)
{
}

Range::Range(int stop) : Range(0, stop)
{
}

size_t Range::size() const noexcept
{
    if (step_ > 0) {
        if (start_ < stop_) {
            return (stop_ - start_ - 1) / step_ + 1;
        }
        else {
            return 0;
        }
    }

    if (start_ > stop_) {
        return (start_ - stop_ - 1) / -step_ + 1;
    }

    return 0;
}

Range::const_iterator Range::begin() const noexcept
{
    return const_iterator(this);
}

Range::const_iterator Range::end() const noexcept
{
    return const_iterator(this, size());
}

int Range::operator[](size_t index) const noexcept
{
    return start_ + index * step_;
}

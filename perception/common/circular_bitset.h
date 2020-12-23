///
/// @file
/// @copyright Copyright (c) 2020. MIT License.
///
#ifndef PERCEPTION_COMMON_CIRCULAR_BITSET_H
#define PERCEPTION_COMMON_CIRCULAR_BITSET_H

#include <algorithm>
#include <bitset>

namespace perception
{

template <std::int32_t max_size>
class CircularBitset
{
  public:
    using value_type = bool;
    using size_type = std::int32_t;
    using reference = typename std::bitset<max_size>::reference;
    using container = std::bitset<max_size>;

    CircularBitset() : bitset_{}, tail_{0}, head_{0}, size_{0}, capacity_{max_size} {}

    explicit CircularBitset(const std::initializer_list<bool> list)
        : bitset_{}, tail_{0}, head_{0}, size_{0}, capacity_{max_size}
    {
        std::for_each(list.begin(), list.end(), [this](const auto& value) { push_back(value); });
    }

    CircularBitset(const CircularBitset& other)
        : bitset_{other.bitset_}, tail_{other.tail_}, head_{other.head_}, size_{other.size_}, capacity_{other.capacity_}
    {
    }

    CircularBitset& operator=(const CircularBitset& other) &
    {
        bitset_ = other.bitset_;
        tail_ = other.tail_;
        head_ = other.head_;
        size_ = other.size_;
        capacity_ = other.capacity_;
    }

    CircularBitset(CircularBitset&& other)
        : bitset_{std::move(other.bitset_)},
          tail_{other.tail_},
          head_{other.head_},
          size_{other.size_},
          capacity_{other.capacity_}
    {
    }

    CircularBitset& operator=(CircularBitset&& other) &
    {
        bitset_ = std::move(other.bitset_);
        tail_ = other.tail_;
        head_ = other.head_;
        size_ = other.size_;
        capacity_ = other.capacity_;
    }

    size_type count() const { return static_cast<size_type>(bitset_.count()); }
    size_type size() const { return size_; }
    size_type capacity() const { return capacity_; }
    bool empty() const { return (0 == size()); }
    bool full() const { return (size() == capacity()); }

    void clear()
    {
        const auto number_of_elements_to_remove{size()};
        for (auto i = 0; i < number_of_elements_to_remove; ++i)
        {
            pop_front();
        }
        bitset_.reset();
        tail_ = 0;
        head_ = 0;
    }

    void resize(const size_type new_size)
    {
        const auto new_capacity = std::min(new_size, static_cast<size_type>(max_size));
        if (capacity_ != new_capacity)
        {
            clear();
            capacity_ = new_capacity;
        }
    }

    void push_back(const value_type value)
    {
        if (full())
        {
            pop_front();
        }
        bitset_.set(static_cast<std::size_t>(tail_), value);
        ++tail_;
        tail_ %= capacity();
        ++size_;
    }

    void pop_front()
    {
        if (!empty())
        {
            bitset_.reset(static_cast<std::size_t>(head_));
            ++head_;
            head_ %= capacity();
            --size_;
        }
    }

    value_type back() const { return at(size() - 1); }
    value_type front() const { return at(0); }

    value_type at(const size_type n) const
    {
        const auto wrapped_index = static_cast<std::size_t>((head_ + n) % capacity());
        return bitset_[wrapped_index];
    }

    reference at(const size_type n)
    {
        const auto wrapped_index = static_cast<std::size_t>((head_ + n) % capacity());
        return bitset_[wrapped_index];
    }

  private:
    std::bitset<max_size> bitset_;
    size_type tail_;
    size_type head_;

    size_type size_;
    size_type capacity_;
};

template <std::int32_t max_size>
bool operator==(const CircularBitset<max_size>& lhs, const CircularBitset<max_size>& rhs) noexcept
{
    bool result = ((!lhs.empty()) && (!rhs.empty()) && (lhs.capacity() == rhs.capacity()) &&
                   (lhs.size() == rhs.size()) && (lhs.count() == rhs.count()));
    if (result)
    {
        bool is_bitset_elements_equal = true;
        for (auto i = 0; i < lhs.size(); ++i)
        {
            is_bitset_elements_equal &= (lhs.at(i) == rhs.at(i));
        }
        result &= is_bitset_elements_equal;
    }
    return result;
}
}  // namespace perception

#endif  /// PERCEPTION_COMMON_CIRCULAR_BITSET_H

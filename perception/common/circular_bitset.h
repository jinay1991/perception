///
/// @file
/// @copyright Copyright (c) 2023. MIT License.
///
#ifndef PERCEPTION_COMMON_CIRCULAR_BITSET_H
#define PERCEPTION_COMMON_CIRCULAR_BITSET_H

#include <algorithm>
#include <bitset>

namespace perception
{

/// @brief Circular Bitset holds bitset of max_size. Each bit represents one boolean state.
///
/// @tparam max_size [in] - Max Bitset size
template <std::int32_t max_size>
class CircularBitset final
{
  public:
    /// @brief Underlying value type
    using value_type = bool;

    /// @brief Container's size type
    using size_type = std::int32_t;

    /// @brief Underlying container
    using container = std::bitset<max_size>;

    /// @brief Container's reference
    using reference = typename container::reference;

    /// @brief Default Constructor
    constexpr CircularBitset() : bitset_{}, tail_{0}, head_{0}, size_{0}, capacity_{max_size} {}

    /// @brief Constructor
    ///
    /// @param list [in] - Initializer list to populate bitset with privided bool list.
    constexpr explicit CircularBitset(const std::initializer_list<bool> list) noexcept
        : bitset_{}, tail_{0}, head_{0}, size_{0}, capacity_{max_size}
    {
        std::for_each(list.begin(), list.end(), [this](const auto& value) { push_back(value); });
    }

    /// @brief Current bit set count
    ///
    /// @return Number of bits set
    constexpr size_type count() const noexcept { return static_cast<size_type>(bitset_.count()); }

    /// @brief Current bit set size
    ///
    /// @return Number of bits filled
    constexpr size_type size() const noexcept { return size_; }

    /// @brief Current bit set capacity
    ///
    /// @return Number of bits can be stored
    constexpr size_type capacity() const noexcept { return capacity_; }

    /// @brief Check if bitset is empty
    ///
    /// @return True if bitset is empty, otherwise False
    constexpr bool empty() const noexcept { return (0 == size()); }

    /// @brief Check if bitset is full (i.e. full capacity)
    ///
    /// @return True if bitset is full, otherwise False
    constexpr bool full() const noexcept { return (size() == capacity()); }

    /// @brief Clear all the elements from the bitset
    constexpr void clear() noexcept
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

    /// @brief Resize current bitset to the new size.
    /// @note Resize is possible only if provided new size is <max_size (compiled-time) value.
    constexpr void resize(const size_type new_size) noexcept
    {
        const auto new_capacity = std::min(new_size, static_cast<size_type>(max_size));
        if (capacity_ != new_capacity)
        {
            clear();
            capacity_ = new_capacity;
        }
    }

    /// @brief Add provided value to bitset at back (i.e. tail)
    ///
    /// @param value [in] - Value
    constexpr void push_back(const value_type value) noexcept
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

    /// @brief Remove head value from bitset front (i.e. head)
    ///
    /// @param value [in] - Value
    constexpr void pop_front() noexcept
    {
        if (!empty())
        {
            bitset_.reset(static_cast<std::size_t>(head_));
            ++head_;
            head_ %= capacity();
            --size_;
        }
    }

    /// @brief Provide value at tail
    ///
    /// @return value at tail
    constexpr value_type back() const noexcept { return at(size() - 1); }

    /// @brief Provide value at head
    ///
    /// @return value at head
    constexpr value_type front() const noexcept { return at(0); }

    /// @brief Value at given index
    ///
    /// @param n [in] - index
    ///
    /// @return value at index (n)
    constexpr value_type at(const size_type n) const noexcept
    {
        const auto wrapped_index = static_cast<std::size_t>((head_ + n) % capacity());
        return bitset_[wrapped_index];
    }

    /// @brief Reference at given index
    ///
    /// @param n [in] - index
    ///
    /// @return reference at index (n)
    constexpr reference at(const size_type n) noexcept
    {
        const auto wrapped_index = static_cast<std::size_t>((head_ + n) % capacity());
        return bitset_[wrapped_index];
    }

  private:
    /// @brief Bitset storage
    std::bitset<max_size> bitset_;

    /// @brief Circular buffer tail index
    size_type tail_;

    /// @brief Circular buffer head index
    size_type head_;

    /// @brief Circular buffer current size
    size_type size_;

    /// @brief Circular buffer current capacity
    size_type capacity_;
};

/// @brief Equality Operator for Circular Bitset for given max_size
///
/// @tparam max_size [in] - Max Bitset size
///
/// @return True if lhs == rhs, otherwise False.
template <std::int32_t max_size>
constexpr bool operator==(const CircularBitset<max_size>& lhs, const CircularBitset<max_size>& rhs) noexcept
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

/// @brief Inequality Operator for Circular Bitset for given max_size
///
/// @tparam max_size [in] - Max Bitset size
///
/// @return True if lhs != rhs, otherwise False.
template <std::int32_t max_size>
constexpr bool operator!=(const CircularBitset<max_size>& lhs, const CircularBitset<max_size>& rhs) noexcept
{
    return (!(lhs == rhs));
}
}  // namespace perception

#endif  /// PERCEPTION_COMMON_CIRCULAR_BITSET_H

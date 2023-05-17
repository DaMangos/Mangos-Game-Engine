#pragma once
#include <compare>
#include <ranges>
#include <type_traits>

namespace handles
{
template <class unmanaged_type>
class unique;

template <class unmanaged_type>
class common final
{
  public:
    typedef unmanaged_type value_type;

    constexpr explicit common() noexcept
    : _unmanaged_object()
    {
    }

    constexpr explicit common(value_type unmanaged_object) noexcept
      requires std::is_fundamental_v<value_type> or std::is_pointer_v<value_type>
    : _unmanaged_object(unmanaged_object)
    {
    }

    constexpr explicit common(value_type const &unmanaged_object) noexcept
    : _unmanaged_object(unmanaged_object)
    {
    }

    constexpr explicit common(value_type &&unmanaged_object) noexcept
    : _unmanaged_object(std::move(unmanaged_object))
    {
    }

    constexpr std::strong_ordering operator<=>(common const &other) const noexcept
    {
      return _unmanaged_object <=> other._unmanaged_object;
    }

    [[nodiscard]]
    constexpr value_type &get() noexcept
    {
      return _unmanaged_object;
    }

    [[nodiscard]]
    constexpr value_type get() const noexcept
    {
      return _unmanaged_object;
    }

    [[nodiscard]]
    constexpr value_type promote(auto &&...deleter_args) const noexcept
    {
      return unique<value_type>(_unmanaged_object, std::move(deleter_args)...);
    }

    [[nodiscard]]
    constexpr value_type *data() noexcept
    {
      return &_unmanaged_object;
    }

    [[nodiscard]]
    constexpr value_type const *data() const noexcept
    {
      return &_unmanaged_object;
    }

    [[nodiscard]]
    constexpr auto *data() noexcept requires std::ranges::contiguous_range<value_type>
    {
      return _unmanaged_object.data();
    }

    [[nodiscard]]
    constexpr auto const *data() const noexcept requires std::ranges::contiguous_range<value_type>
    {
      return _unmanaged_object.data();
    }

    [[nodiscard]]
    constexpr value_type release() noexcept
    {
      value_type managed_object = _unmanaged_object;
      _unmanaged_object         = value_type();
      return managed_object;
    }

    constexpr void reset(value_type unmanaged_object = value_type()) noexcept
    {
      _unmanaged_object = unmanaged_object;
    }

    constexpr void swap(common &other) noexcept(std::is_nothrow_swappable_v<unmanaged_type>)
    {
      std::swap(other._unmanaged_object, _unmanaged_object);
    }

  private:
    value_type _unmanaged_object;
};
}

template <class unmanaged_type>
struct std::hash<handles::common<unmanaged_type>>
{
    constexpr std::size_t operator()(handles::common<unmanaged_type> const &handle) const noexcept
    {
      return std::hash<unmanaged_type>{}(handle.get());
    }
};
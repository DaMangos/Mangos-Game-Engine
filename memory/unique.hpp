#pragma once
#include <ranges>
#include <type_traits>

namespace handles
{
template <class unmanaged_type>
class common;

template <class deleting_type>
class deleter;

template <class managed_type>
class unique final
{
  public:
    typedef managed_type        value_type;
    typedef deleter<value_type> deleter_type;

    constexpr explicit unique(auto &&...deleter_args) noexcept
    : _managed_object(),
      _deleter(std::move(deleter_args)...)
    {
    }

    constexpr explicit unique(value_type managed_object, auto &&...deleter_args) noexcept
    requires std::is_fundamental_v<value_type> or std::is_pointer_v<value_type>
    : _managed_object(managed_object),
      _deleter(std::move(deleter_args)...)
    {
    }

    constexpr explicit unique(value_type &&managed_object, auto &&...deleter_args) noexcept
    : _managed_object(std::move(managed_object)),
      _deleter(std::move(deleter_args)...)
    {
    }

    constexpr unique(unique &&other) noexcept
    : _managed_object(other.release()),
      _deleter(other._deleter)
    {
    }

    constexpr unique &operator=(unique &&other) noexcept
    {
      reset(other.release());
      _deleter = other._deleter;
      return *this;
    }

    constexpr std::strong_ordering operator<=>(unique const &other) const noexcept
    {
      return _managed_object <=> other._managed_object;
    }

    [[nodiscard]]
    constexpr value_type get() const noexcept
    {
      return _managed_object;
    }

    [[nodiscard]]
    constexpr value_type demote() const noexcept
    {
      return common<value_type>(_managed_object);
    }

    [[nodiscard]]
    constexpr value_type *data() noexcept
    {
      reset();
      return &_managed_object;
    }

    [[nodiscard]]
    constexpr auto *data() noexcept
    requires std::ranges::contiguous_range<value_type>
    {
      reset();
      return _managed_object.data();
    }

    [[nodiscard]]
    constexpr value_type release() noexcept
    {
      value_type managed_object = _managed_object;
      _managed_object           = value_type();
      return managed_object;
    }

    constexpr void reset(value_type managed_object = value_type()) noexcept
    {
      if (_managed_object != value_type())
        _deleter(_managed_object);
      _managed_object = managed_object;
    }

    constexpr void swap(unique &other) noexcept(std::is_nothrow_swappable_v<managed_type>)
    {
      std::swap(other._managed_object, _managed_object);
      std::swap(other._deleter, _deleter);
    }

    constexpr ~unique()
    {
      reset();
    }

    unique(unique const &) = delete;

    unique &operator=(unique const &) = delete;

  private:
    value_type   _managed_object;
    deleter_type _deleter;
};
}

template <class unmanaged_type>
struct std::hash<handles::unique<unmanaged_type>>
{
    constexpr std::size_t operator()(handles::unique<unmanaged_type> const &handle) const noexcept
    {
      return std::hash<unmanaged_type>{}(handle.get());
    }
};
#include <iostream>
#include <vk/ext/debug_utils_messenger.hpp>

namespace graphics::vk
{
constexpr debug_utils_messenger::debug_utils_messenger(private_type &&debug_utils_messenger) noexcept
: _underling(std::move(debug_utils_messenger))
{
}

constexpr debug_utils_messenger::public_type debug_utils_messenger::get() const noexcept
{
  return public_type(_underling.get());
}
}
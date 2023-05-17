#pragma once

#include <vk/ext/deleter.hpp>
#include <vk/unique_handle.hpp>

namespace graphics::vk
{
class debug_utils_messenger final
{
  public:
    typedef common_handle<VkDebugUtilsMessengerEXT> public_type;
    typedef unique_handle<VkDebugUtilsMessengerEXT> private_type;

    constexpr explicit debug_utils_messenger(private_type &&debug_utils_messenger) noexcept;

    [[nodiscard]]
    constexpr public_type get() const noexcept;

  private:
    private_type _underling;
};
}
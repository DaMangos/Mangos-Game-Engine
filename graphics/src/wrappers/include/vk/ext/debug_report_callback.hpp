#pragma once

#include <vk/ext/deleter.hpp>
#include <vk/unique_handle.hpp>

namespace graphics::vk
{
class debug_report_callback final
{
  public:
    typedef common_handle<VkDebugReportCallbackEXT> public_type;
    typedef unique_handle<VkDebugReportCallbackEXT> private_type;

    constexpr explicit debug_report_callback(private_type &&debug_report_callback) noexcept;

    [[nodiscard]]
    constexpr public_type get() const noexcept;

  private:
    private_type _underling;
};
}
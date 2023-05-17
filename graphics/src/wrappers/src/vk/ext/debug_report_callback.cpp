#include <iostream>
#include <vk/ext/debug_report_callback.hpp>

namespace graphics::vk
{
constexpr debug_report_callback::debug_report_callback(unique_handle<VkDebugReportCallbackEXT> &&debug_report_callback) noexcept
: _underling(std::move(debug_report_callback))
{
}

constexpr debug_report_callback::public_type debug_report_callback::get() const noexcept
{
  return public_type(_underling.get());
}
}
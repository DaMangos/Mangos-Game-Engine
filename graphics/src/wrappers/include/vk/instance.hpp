#pragma once

#include <glfw/common_handle.hpp>
#include <string_view>
#include <vector>
#include <vk/ext/deleter.hpp>
#include <vk/unique_handle.hpp>

namespace graphics::vk
{
[[nodiscard]]
unique_handle<VkInstance> make_instance(VkInstanceCreateInfo create_info);

class instance final
{
  public:
    typedef common_handle<VkInstance> public_type;
    typedef unique_handle<VkInstance> private_type;

    constexpr explicit instance(private_type &&underling_instance) noexcept;

    [[nodiscard]]
    constexpr public_type get() const noexcept;

    [[nodiscard]]
    std::vector<common_handle<VkPhysicalDevice>> enumerate_Physical_device() const;

    [[nodiscard]]
    unique_handle<VkDebugUtilsMessengerEXT> create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const;

    [[nodiscard]]
    unique_handle<VkDebugReportCallbackEXT> create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const;

    [[nodiscard]]
    unique_handle<VkSurfaceKHR> create_surface(glfw::common_handle<GLFWwindow> window) const;

    template <class function_pointer>
    auto invoke(std::string const &function_name, auto &&...function_args) const
    {
      return graphics::vk::invoke<function_pointer>(get(), function_name, std::move(function_args)...);
    }

  private:
    private_type _underling_instance;
};
}
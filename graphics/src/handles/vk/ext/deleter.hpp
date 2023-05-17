#pragma once

#include <vk/deleter.hpp>
#include <vk/invoke.hpp>

namespace graphics::vk
{
template <>
class deleter<VkDebugReportCallbackEXT>
{
  public:
    deleter(common_handle<VkInstance> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkDebugReportCallbackEXT victim) const noexcept
    {
      invoke<PFN_vkDestroyDebugReportCallbackEXT>(_dispatcher,
                                                  "vkDestroyDebugReportCallbackEXT",
                                                  _dispatcher.get(),
                                                  victim,
                                                  nullptr);
    }

  private:
    common_handle<VkInstance> _dispatcher;
};

template <>
class deleter<VkDebugUtilsMessengerEXT>
{
  public:
    deleter(common_handle<VkInstance> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkDebugUtilsMessengerEXT victim) const noexcept
    {
      invoke<PFN_vkDestroyDebugUtilsMessengerEXT>(_dispatcher,
                                                  "vkDestroyDebugUtilsMessengerEXT",
                                                  _dispatcher.get(),
                                                  victim,
                                                  nullptr);
    }

  private:
    common_handle<VkInstance> _dispatcher;
};
}
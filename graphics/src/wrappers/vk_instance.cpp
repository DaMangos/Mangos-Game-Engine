// #include "vk_instance.hpp"

// namespace graphics::vk
// {
// constexpr instance::instance(VkInstanceCreateInfo create_info)
// {
//   if (vkCreateInstance(&create_info, nullptr, _underling_instance.override()) != VK_SUCCESS)
//     throw std::runtime_error("failed to create VkInstance");
// }

// constexpr common_handle<VkInstance> instance::get() const noexcept
// {
//   return common_handle<VkInstance>(_underling_instance.get());
// }

// std::vector<common_handle<VkPhysicalDevice>> instance::enumerate_Physical_device() const
// {
//   std::uint32_t count = 0;
//   vkEnumeratePhysicalDevices(_underling_instance.get(), &count, nullptr);
//   std::vector<VkPhysicalDevice> physical_devices(static_cast<std::vector<VkPhysicalDevice>::size_type>(count));
//   vkEnumeratePhysicalDevices(_underling_instance.get(), &count, physical_devices.data());
//   return std::vector<common_handle<VkPhysicalDevice>>(physical_devices.begin(), physical_devices.end());
// }

// unique_handle<VkDebugUtilsMessengerEXT>
// instance::create_debug_utils_messenger(VkDebugUtilsMessengerCreateInfoEXT create_info) const
// {
//   unique_handle<VkDebugUtilsMessengerEXT> debug_utils_messenger(get());
//   if (invoke<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT",
//                                                  _underling_instance.get(),
//                                                  &create_info,
//                                                  nullptr,
//                                                  debug_utils_messenger.override()) != VK_SUCCESS)
//     throw std::runtime_error("failed to create VkDebugUtilsMessengerEXT");
//   return debug_utils_messenger;
// }

// unique_handle<VkDebugReportCallbackEXT>
// instance::create_debug_report_callback(VkDebugReportCallbackCreateInfoEXT create_info) const
// {
//   unique_handle<VkDebugReportCallbackEXT> debug_report_callback(get());
//   if (invoke<PFN_vkCreateDebugReportCallbackEXT>("vkCreateDebugReportCallbackEXT",
//                                                  _underling_instance.get(),
//                                                  &create_info,
//                                                  nullptr,
//                                                  debug_report_callback.override()) != VK_SUCCESS)
//     throw std::runtime_error("failed to create VkDebugReportCallbackEXT");
//   return debug_report_callback;
// }

// unique_handle<VkSurfaceKHR> instance::create_surface(glfw::common_handle<GLFWwindow> window) const
// {
//   unique_handle<VkSurfaceKHR> surface(get());
//   if (glfwCreateWindowSurface(_underling_instance.get(), window.get(), nullptr, surface.override()) != VK_SUCCESS)
//     throw std::runtime_error("failed to create VkSurfaceKHR");
//   return surface;
// }
// }
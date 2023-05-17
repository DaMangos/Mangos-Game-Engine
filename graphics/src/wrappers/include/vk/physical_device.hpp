#pragma once

#include <vk/unique_handle.hpp>

namespace graphics::vk
{
class physical_device final
{
  public:
    typedef common_handle<VkPhysicalDevice> public_type;
    typedef common_handle<VkPhysicalDevice> private_type;

    constexpr explicit physical_device(private_type &&physical_device) noexcept;

    [[nodiscard]]
    constexpr public_type get() const noexcept;

    [[nodiscard]]
    unique_handle<VkDevice> create_device(VkDeviceCreateInfo create_info) const;

    [[nodiscard]]
    bool check_surface_support(common_handle<VkSurfaceKHR> surface, std::uint32_t queue_family) const;

    [[nodiscard]]
    VkSurfaceCapabilitiesKHR get_surface_capabilities(common_handle<VkSurfaceKHR> surface) const;

    [[nodiscard]]
    std::vector<VkSurfaceFormatKHR> get_surface_formats(common_handle<VkSurfaceKHR> surface) const;

    [[nodiscard]]
    std::vector<VkPresentModeKHR> get_present_modes(common_handle<VkSurfaceKHR> surface) const;

    [[nodiscard]]
    VkPhysicalDeviceFeatures get_features() const noexcept;

    [[nodiscard]]
    VkPhysicalDeviceProperties get_properties() const noexcept;

    [[nodiscard]]
    std::vector<VkExtensionProperties> get_extension_properties() const;

    [[nodiscard]]
    std::vector<VkQueueFamilyProperties> get_queue_family_properties() const;

  public:
    private_type _underling;
};
}
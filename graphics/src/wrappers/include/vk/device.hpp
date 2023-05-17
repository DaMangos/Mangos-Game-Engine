#pragma once

#include <vk/unique_handle.hpp>

namespace graphics::vk
{
class device final
{
  public:
    typedef common_handle<VkDevice> public_type;
    typedef unique_handle<VkDevice> private_type;

    constexpr explicit device(private_type &&device) noexcept;

    [[nodiscard]]
    constexpr public_type get() const noexcept;

    [[nodiscard]]
    unique_handle<std::vector<VkCommandBuffer>> allocate_command_buffers(common_handle<VkCommandPool> command_pool,
                                                                         VkCommandBufferAllocateInfo  allocate_info) const;

    [[nodiscard]]
    unique_handle<VkCommandPool> create_command_pool(VkCommandPoolCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkFence> create_fence(VkFenceCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkFramebuffer> create_framebuffer(VkFramebufferCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkImageView> create_image_view(VkImageViewCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkPipelineLayout> create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkPipeline> create_compute_pipeline(VkComputePipelineCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkPipeline> create_graphics_pipeline(VkGraphicsPipelineCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkRenderPass> create_render_pass(VkRenderPassCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkSemaphore> create_semaphore(VkSemaphoreCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkShaderModule> create_shader_module(VkShaderModuleCreateInfo create_info) const;

    [[nodiscard]]
    unique_handle<VkSwapchainKHR> create_swapchain(VkSwapchainCreateInfoKHR create_info) const;

  private:
    private_type _underling;
};
}
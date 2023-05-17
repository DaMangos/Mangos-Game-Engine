#include <vk/device.hpp>

namespace graphics::vk
{
constexpr device::device(private_type &&device) noexcept
: _underling(std::move(device))
{
}

constexpr device::public_type device::get() const noexcept
{
  return public_type(_underling.get());
}

unique_handle<std::vector<VkCommandBuffer>> device::allocate_command_buffers(common_handle<VkCommandPool> command_pool,
                                                                             VkCommandBufferAllocateInfo  allocate_info) const
{
  std::vector<VkCommandBuffer> command_buffers(
    static_cast<std::vector<VkCommandBuffer>::size_type>(allocate_info.commandBufferCount));

  vkAllocateCommandBuffers(_underling.get(), &allocate_info, command_buffers.data());
  return unique_handle<std::vector<VkCommandBuffer>>(std::move(command_buffers), _underling.get(), command_pool);
}

unique_handle<VkCommandPool> device::create_command_pool(VkCommandPoolCreateInfo create_info) const
{
}

unique_handle<VkFence> device::create_fence(VkFenceCreateInfo create_info) const
{
}

unique_handle<VkFramebuffer> device::create_framebuffer(VkFramebufferCreateInfo create_info) const
{
}

unique_handle<VkImageView> device::create_image_view(VkImageViewCreateInfo create_info) const
{
}

unique_handle<VkPipelineLayout> device::create_pipeline_layout(VkPipelineLayoutCreateInfo create_info) const
{
}

unique_handle<VkPipeline> device::create_compute_pipeline(VkComputePipelineCreateInfo create_info) const
{
}

unique_handle<VkPipeline> device::create_graphics_pipeline(VkGraphicsPipelineCreateInfo create_info) const
{
}

unique_handle<VkRenderPass> device::create_render_pass(VkRenderPassCreateInfo create_info) const
{
}

unique_handle<VkSemaphore> device::create_semaphore(VkSemaphoreCreateInfo create_info) const
{
}

unique_handle<VkShaderModule> device::create_shader_module(VkShaderModuleCreateInfo create_info) const
{
}

unique_handle<VkSwapchainKHR> device::create_swapchain(VkSwapchainCreateInfoKHR create_info) const
{
}
}
#pragma once

#include <handles.hpp>
#include <vk/to_count.hpp>
#include <vk/to_data.hpp>

namespace graphics::vk
{
template <class victim_type>
class deleter final
{
    deleter() = delete;
};

template <>
class deleter<VkBuffer>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkBuffer victim) const noexcept
    {
      vkDestroyBuffer(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkBufferView>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkBufferView victim) const noexcept
    {
      vkDestroyBufferView(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<std::vector<VkCommandBuffer>>
{
  public:
    deleter(common_handle<VkDevice> dispatcher, common_handle<VkCommandPool> command_pool)
    : _dispatcher(dispatcher),
      _command_pool(command_pool)
    {
    }

    inline void operator()(std::vector<VkCommandBuffer> &victims) const noexcept
    {
      vkFreeCommandBuffers(_dispatcher.get(), _command_pool.get(), to_count(victims), to_data(victims));
    }

  private:
    common_handle<VkDevice>      _dispatcher;
    common_handle<VkCommandPool> _command_pool;
};

template <>
class deleter<VkCommandPool>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkCommandPool victim) const noexcept
    {
      vkDestroyCommandPool(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkDescriptorPool>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkDescriptorPool victim) const noexcept
    {
      vkDestroyDescriptorPool(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkDescriptorSetLayout>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkDescriptorSetLayout victim) const noexcept
    {
      vkDestroyDescriptorSetLayout(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkDevice>
{
  public:
    inline void operator()(VkDevice victim) const noexcept
    {
      vkDestroyDevice(victim, nullptr);
    }
};

template <>
class deleter<VkFence>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkFence victim) const noexcept
    {
      vkDestroyFence(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkFramebuffer>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkFramebuffer victim) const noexcept
    {
      vkDestroyFramebuffer(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkImage>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkImage victim) const noexcept
    {
      vkDestroyImage(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkImageView>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkImageView victim) const noexcept
    {
      vkDestroyImageView(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkInstance>
{
  public:
    inline void operator()(VkInstance victim) const noexcept
    {
      vkDestroyInstance(victim, nullptr);
    }
};

template <>
class deleter<VkSurfaceKHR>
{
  public:
    deleter(common_handle<VkInstance> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkSurfaceKHR victim) const noexcept
    {
      vkDestroySurfaceKHR(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkInstance> _dispatcher;
};

template <>
class deleter<VkSwapchainKHR>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkSwapchainKHR victim) const noexcept
    {
      vkDestroySwapchainKHR(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkPipeline>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkPipeline victim) const noexcept
    {
      vkDestroyPipeline(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkPipelineCache>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkPipelineCache victim) const noexcept
    {
      vkDestroyPipelineCache(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkPipelineLayout>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkPipelineLayout victim) const noexcept
    {
      vkDestroyPipelineLayout(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkRenderPass>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkRenderPass victim) const noexcept
    {
      vkDestroyRenderPass(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkSampler>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkSampler victim) const noexcept
    {
      vkDestroySampler(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkSemaphore>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkSemaphore victim) const noexcept
    {
      vkDestroySemaphore(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};

template <>
class deleter<VkShaderModule>
{
  public:
    deleter(common_handle<VkDevice> dispatcher)
    : _dispatcher(dispatcher)
    {
    }

    inline void operator()(VkShaderModule victim) const noexcept
    {
      vkDestroyShaderModule(_dispatcher.get(), victim, nullptr);
    }

  private:
    common_handle<VkDevice> _dispatcher;
};
}
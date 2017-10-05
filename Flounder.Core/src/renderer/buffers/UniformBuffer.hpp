﻿#pragma once

#include "Buffer.hpp"
#include "../pipelines/Descriptor.hpp"

namespace Flounder
{
	class UniformBuffer :
		public Buffer
	{
	private:
		VkDeviceSize m_size;
	public:
		UniformBuffer(const VkDeviceSize &size);

		~UniformBuffer();

		void Create();

		void Cleanup();

		void Update(void *newData);

		static DescriptorType CreateDescriptor(const uint32_t &binding, const VkShaderStageFlags &stage);

		VkWriteDescriptorSet GetWriteDescriptor(const uint32_t &binding, const VkDescriptorSet &descriptorSet);

		VkDeviceSize GetSize() const { return m_size; }
	};
}
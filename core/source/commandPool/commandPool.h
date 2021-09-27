#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
namespace natural {
	class CommandBuffer;
	class CommandPool {
	public:
		virtual ~CommandPool() = default;
		virtual void CreatePrimaryBuffers(size_t count) = 0;
		virtual void CreateSecondaryBuffers(size_t count) = 0;
		virtual size_t GetPrimaryBufferCount() const = 0;
		virtual size_t GetSecondaryBufferCount() const = 0;
		virtual CommandBuffer* GetPrimaryBuffer(size_t index) const = 0;
		virtual CommandBuffer* GetSecondaryBuffer(size_t index) const = 0;
		class Impl;
	};
}
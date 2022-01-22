#pragma once
#include "../common.h"
namespace natural {
	class CommandBuffer;
	class CommandPool {
	public:
		virtual ~CommandPool() = default;
		virtual void CreatePrimaryBuffer(std::unique_ptr<CommandBuffer>& buffer) = 0;
		virtual void CreateSecondaryBuffer(std::unique_ptr<CommandBuffer>& buffer) = 0;
		class Impl;
	};
}
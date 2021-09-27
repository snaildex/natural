#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
namespace natural {
	class Fence {
	public:
		virtual ~Fence() = default;
		class Impl;
		virtual void Reset() = 0;
		virtual bool IsSignaled() = 0;
	};
}
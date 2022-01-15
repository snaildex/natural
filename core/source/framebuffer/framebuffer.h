#pragma once
#include "../common.h"
namespace natural {
	class Framebuffer {
	public:
		virtual ~Framebuffer() = default;
		class Impl;
	};
}
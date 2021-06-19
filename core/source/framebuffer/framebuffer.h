#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
namespace natural {
	class Framebuffer {
	public:
		virtual ~Framebuffer() = default;
		class Impl;
	};
}
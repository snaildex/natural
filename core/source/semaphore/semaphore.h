#pragma once
#include "../common.h"
namespace natural {
	class Semaphore {
	public:
		virtual ~Semaphore() = default;
		class Impl;
	};
}
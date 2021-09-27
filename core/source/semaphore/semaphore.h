#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
namespace natural {
	class Semaphore {
	public:
		virtual ~Semaphore() = default;
		class Impl;
	};
}
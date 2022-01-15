#pragma once
#include "../common.h"
namespace natural {
	class ImageView {
	public:
		virtual ~ImageView() = default;
		class Impl;
	};
}
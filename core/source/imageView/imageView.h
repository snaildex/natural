#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
namespace natural {
	class ImageView {
	public:
		virtual ~ImageView() = default;
		class Impl;
	};
}
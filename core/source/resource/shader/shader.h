#pragma once
#include "../../common.h"
#include "../../helpers/helpers.h"
#include "../resource.h"
namespace natural {
	class Shader : public Resource {
	public:
		virtual ~Shader() = default;
		class Impl;
	};
}
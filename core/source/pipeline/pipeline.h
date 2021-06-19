#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
#include "../object/object.h"
#include "../renderPass/renderPass.h"
namespace natural {
	class Shader;
	class Pipeline : public Object {
	public:
		virtual ~Pipeline() = default;
		class Impl;
	};
}
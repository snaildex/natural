#pragma once
#include "resource.h"
#include "../application/applicationImpl.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
namespace natural {
	void RegisterResourceBuilders();
	Resource* BuildResource(Application::Impl* app, const json& config);
}
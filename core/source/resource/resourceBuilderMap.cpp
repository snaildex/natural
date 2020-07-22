#include "resourceBuilderMap.h"
#include "pipeline/pipelineImpl.h"
namespace natural {
	typedef std::function<Resource * (Application::Impl*, const json&)> ResourceBuilder;
	std::map<std::string, ResourceBuilder> ResourceBuilderMap;

	void AddResourceBuilder(const std::string& TypeName, ResourceBuilder builder) {
		ResourceBuilderMap[TypeName] = builder;
		Log("Registered resource type %s", TypeName.data());
	}

	template<typename T>
	void RegisterResourceBuilder(const std::string& name) { AddResourceBuilder(name, T::Impl::Create); }

	void RegisterResourceBuilders() {
		RegisterResourceBuilder<Pipeline>("pipeline");
	}

	Resource* BuildResource(Application::Impl* app, const json& config) {
		if (!config.contains("type")) return nullptr;
		if (!config.contains("name")) return nullptr;
		std::string type = config["type"];
		auto t = ResourceBuilderMap.find(type);
		if (t == ResourceBuilderMap.cend()) return nullptr;
		Resource* r;
		{
			LogIndent();
			r = t->second(app, config);
		}
		if (r) Log("Builded resource %s %s", r->GetName().data(), r->PrintTags().data());
		return r;
	}
}
#pragma once
#include "common.h"
#include "helpers/helpers.h"
#include "applicationListener.h"
#include "../resource/resource.h"
#include "../enums/format.h"
#include "../renderPass/renderPassDesc.h"
namespace natural {
	class Application {
		Entity(Application)
	protected:
		std::unique_ptr<ApplicationListener> m_listener;
		std::list<std::unique_ptr<Resource>> m_resources;
		void ScanResources();
	public:
		class Impl;
		Application() = default;
		virtual ~Application() = default;
		static Application* Create(int width, int height, const std::string& name, ApplicationListener* listener);
		virtual void Run() = 0;
		void AddResource(Resource* resource) { m_resources.emplace_back(resource); }
		Resource* GetResource(std::function<bool(const Resource*)> predicate) {
			for (const auto& res : m_resources) if (predicate(res.get())) return res.get();
			return nullptr;
		}
		virtual Format GetSwapChainImageFormat() const = 0;
	};
}
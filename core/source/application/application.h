#pragma once
#include "common.h"
#include "helpers/helpers.h"
#include "../resource/resource.h"
namespace natural {
	class Application;
	class ApplicationListener {
		Application* m_app;
	public:
		virtual ~ApplicationListener() = default;
		Application* Application() { return m_app; }
		virtual void Start() = 0;
		virtual void Update() = 0;
		friend class Application;
	};
	class RenderPass;
	class Application {
		Entity(Application)
	protected:
		std::unique_ptr<ApplicationListener> m_listener;
		std::list<std::unique_ptr<Resource>> m_resources;
		void ScanResources();
	private:
		template<class T> T* GetResource(std::function<bool(const T*)> predicate) {
			for (const auto& res : m_resources) {
				T* r = dynamic_cast<T*>(res.get());
				if (r != nullptr && predicate(r)) return r;
			}
			return nullptr;
		}
	public:
		class Impl;
		Application() = default;
		virtual ~Application() = default;
		static Application* Create(int width, int height, const std::string& name, ApplicationListener* listener);
		virtual void Run() = 0;
		void AddResource(Resource* resource) { m_resources.emplace_back(resource); }
		template<class T> T* GetResource(const std::string& name) { return GetResource<T>([&](const T* res) { return res->GetName() == name; }); }
		template<class T> T* GetResource(const std::vector<std::string>& tags) { return GetResource<T>([&](const T* res) { return res->HasTags(tags); }); }
		RenderPass* CreateRenderPass();
	};
}
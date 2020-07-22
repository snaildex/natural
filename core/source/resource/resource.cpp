#include "resource.h"
#include "resourceBuilderMap.h"
namespace natural {
	Resource::Resource()
	{
		m_loadState = LoadState::Unloaded;
	}
	Resource::~Resource()
	{
	}
	void Resource::StartLoading()
	{
		if (m_loadState == LoadState::Loaded || m_loadState == LoadState::Loading) return;
		if (m_loadState == LoadState::Unloading) if (m_unloading.valid()) m_unloading.wait();
		m_loadState = LoadState::Loading;
		m_loading = std::async([this] {
			Log("Starting loading %s %s", typeid(*this).name(), GetName().data());
			Load();
			m_loadState = LoadState::Loaded;
			Log("Finished loading %s %s", typeid(*this).name(), GetName().data());
			});
	}
	void Resource::WaitForLoad()
	{
		if (m_loading.valid()) m_loading.get();
	}
	void Resource::StartUnloading()
	{
		if (m_loadState == LoadState::Unloaded || m_loadState == LoadState::Unloading) return;
		if (m_loadState == LoadState::Loading) if (m_loading.valid()) m_loading.get();
		m_loadState = LoadState::Unloading;
		m_unloading = std::async([this] {
			Log("Starting unloading %s %s", typeid(*this).name(), GetName().data());
			Unload();
			m_loadState = LoadState::Unloaded;
			Log("Finished unloading %s %s", typeid(*this).name(), GetName().data());
			});
	}
	void Resource::WaitForUnload()
	{
		if (m_unloading.valid()) m_unloading.get();
	}
	void Resource::EnsureLoaded()
	{
		if (m_loadState == LoadState::Loaded) return;
		if (m_loadState == LoadState::Unloading) if (m_unloading.valid()) m_unloading.get();
		if (m_loadState == LoadState::Unloaded)  StartLoading();
		WaitForLoad();
	}
}
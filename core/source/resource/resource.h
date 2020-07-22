#pragma once
#include "../common.h"
#include "../helpers/helpers.h"
#include "../object/object.h"
namespace natural {
	class Resource : public Object {
	public:
		enum class LoadState {
			Unloaded,
			Loading,
			Loaded,
			Unloading
		};
	private:
		std::atomic<LoadState> m_loadState;
		std::future<void> m_loading;
		std::future<void> m_unloading;
	protected:
		virtual void Load() = 0;
		virtual void Unload() = 0;
	public:
		Resource();
		virtual ~Resource();
		void StartLoading();
		void WaitForLoad();
		void StartUnloading();
		void WaitForUnload();
		void EnsureLoaded();
	};
}
#pragma once
#include <vector>
namespace natural {
	template <typename T, typename I = T::Impl> I* impl(T* object) { return reinterpret_cast<I*>(object); }
	template <typename T, typename I = T::Impl> const I* impl(const T* object) { return reinterpret_cast<const I*>(object); }
	template <typename H, class C> void CollectVkHandles(std::vector<H>& handles, const C& input) {
		handles.clear();
		for (C::value_type it : input) handles.push_back(impl(it)->GetHandle());
	}
}
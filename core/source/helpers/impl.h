#pragma once
namespace natural {
	template <typename T, typename I = T::Impl> I* impl(T* object) { return reinterpret_cast<I*>(object); }
	template <typename T, typename I = T::Impl> const I* impl(const T* object) { return reinterpret_cast<const I*>(object); }
}
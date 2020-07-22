#include "object.h"
namespace natural {
	Object::Object() {
		m_name = "New object";
	}

	void Object::CopyNameTagsFrom(const Object* source) noexcept {
		m_name = source->m_name;
		m_tags = source->m_tags;
	}

	bool Object::HasTags(const std::vector<std::string>& tags) const noexcept
	{
		for (const auto& tag : tags)
			if (!HasTag(tag))
				return false;
		return true;
	}

	std::string Object::PrintTags() {
		if (m_tags.size() == 0)
			return std::string();
		std::stringstream s;
		s << '(';
		for (const auto& tag : m_tags) {
			s << tag;
			s << ", ";
		}
		s.seekp(-2, std::ios_base::end);
		s << ')';
		return s.str();
	}
}
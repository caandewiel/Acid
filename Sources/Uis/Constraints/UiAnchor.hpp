#pragma once

#include "Export.hpp"

namespace acid {
class ACID_EXPORT UiAnchor {
public:
	explicit constexpr UiAnchor(float value) : m_value(value) {}
	constexpr float Get() const { return m_value; }

	bool operator==(const UiAnchor &rhs) const {
		return m_value == rhs.m_value;
	}

	bool operator!=(const UiAnchor &rhs) const {
		return !operator==(rhs);
	}

	static const UiAnchor Zero;
	static const UiAnchor Left;
	static const UiAnchor Top;
	static const UiAnchor Centre;
	static const UiAnchor Right;
	static const UiAnchor Bottom;

private:
	float m_value;
};
}
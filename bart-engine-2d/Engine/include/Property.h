#pragma once

#include <EPropertyType.h>
#include <Color.h>
#include <string>

namespace bart
{
	class Property
	{
	public:
		virtual ~Property() = default;
		EPropertyType GetType() const { return m_Type; }

	protected:
		EPropertyType m_Type{PT_STRING};
	};

	class BoolProperty final : public Property
	{
	public:
		BoolProperty();
		virtual ~BoolProperty() = default;
		bool Value{false};
	};

	class ColorProperty final : public Property
	{
	public:
		ColorProperty();
		virtual ~ColorProperty() = default;
		void SetFromHex(const std::string& aHexValue);
		Color Value{255, 255, 255};
	};

	class FloatProperty final : public Property
	{
	public:
		FloatProperty();
		virtual ~FloatProperty() = default;
		float Value{0.0f};
	};

	class StringProperty final : public Property
	{
	public:
		StringProperty();
		virtual ~StringProperty() = default;
		std::string Value;
	};

	class IntProperty final : public Property
	{
	public:
		IntProperty();
		virtual ~IntProperty() = default;
		int Value{0};
	};
}

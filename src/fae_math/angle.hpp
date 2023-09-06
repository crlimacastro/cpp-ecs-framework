#pragma once

namespace fae
{
	constexpr float pi = 3.14159265358979323846f;

	constexpr float to_degrees(float radians) { return radians * 180.f / pi; }
	constexpr float to_radians(float degrees) { return degrees * pi / 180.f; }

	struct angle
	{
		static angle from_radians(float radians)
		{
			return angle(radians);
		}

		static angle from_degrees(float degrees)
		{
			return angle(to_radians(degrees));
		}

		float as_radians() const
		{
			return _radians;
		}

		float as_degrees() const
		{
			return to_degrees(_radians);
		}

	private:
		angle(float radians) : _radians(radians) {}
		float _radians;
	};
}
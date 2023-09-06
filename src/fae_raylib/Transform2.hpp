#pragma once
#include <raylib-cpp.hpp>

namespace raylib {
	class Transform2 {
	public:
		Transform2() : translation{ { 0, 0 } }, rotation{ 0 } {}

		GETTERSETTER(Vector2, Translation, translation)
			GETTERSETTER(float, Rotation, rotation)

	private:
		raylib::Vector2 translation{};
		float rotation{};
	};
}  // namespace raylib

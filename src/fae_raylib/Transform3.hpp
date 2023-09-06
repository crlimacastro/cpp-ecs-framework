#pragma once
#include <raylib-cpp.hpp>
#include "raylib_operator_overloads.hpp"

namespace raylib {
	/**
	 * Transform3 type
	 */
	class Transform3 : public ::Transform {
	public:
		Transform3(const ::Transform& transform) : ::Transform{ transform.translation, transform.rotation, transform.scale } {}
		Transform3(Vector3 translation, Quaternion rotation, Vector3 scale) : ::Transform{ translation, rotation, scale } {}
		Transform3() : ::Transform{ { 0, 0, 0 }, { 0, 0, 0, 1 }, { 1, 1, 1 } } {}

		GETTERSETTER(Vector3, Translation, translation)
			GETTERSETTER(Quaternion, Rotation, rotation)
			GETTERSETTER(Vector3, Scale, scale)

			Transform& operator=(const ::Transform& transform) {
			set(transform);
			return *this;
		}

		bool operator==(const ::Transform& other) const {
			return translation == other.translation
				&& rotation == other.rotation
				&& scale == other.scale;
		}

		bool operator!=(const ::Transform& other) {
			return !(*this == other);
		}

		Matrix ToMatrix() const {
			return MatrixScale(scale.x, scale.y, scale.z) * MatrixRotateZYX(QuaternionToEuler(rotation)) * MatrixTranslate(translation.x, translation.y, translation.z);
		}

		operator Matrix() const {
			return ToMatrix();
		}

	private:
		void set(const ::Transform& transform) {
			translation = transform.translation;
			rotation = transform.rotation;
			scale = transform.scale;
		}
	};
	using Transform = Transform3;
}  // namespace raylib

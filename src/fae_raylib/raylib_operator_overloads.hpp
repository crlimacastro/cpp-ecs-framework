#pragma once
#include <raylib.h>

constexpr Vector2 operator+(const Vector2& lhs, const Vector2& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }
constexpr Vector2 operator-(const Vector2& lhs, const Vector2& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
constexpr Vector2 operator*(const float& lhs, const Vector2& rhs) { return { lhs * rhs.x, lhs * rhs.y }; }
constexpr float operator*(const Vector2& lhs, const Vector2& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }
constexpr float operator^(const Vector2& lhs, const Vector2& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }
constexpr bool operator==(const Vector2& lhs, const Vector2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
constexpr bool operator!=(const Vector2& lhs, const Vector2& rhs) { return !(lhs == rhs); }
constexpr Vector3 operator+(const Vector3& lhs, const Vector3& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z }; }
constexpr Vector3 operator-(const Vector3& lhs, const Vector3& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z }; }
constexpr Vector3 operator*(const float& lhs, const Vector3& rhs) { return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z }; }
constexpr float operator*(const Vector3& lhs, const Vector3& rhs) { return { (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z) }; }
constexpr Vector3 operator^(const Vector3& lhs, const Vector3& rhs) { return { lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x }; }
constexpr bool operator==(const Vector3& lhs, const Vector3& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
constexpr bool operator!=(const Vector3& lhs, const Vector3& rhs) { return !(lhs == rhs); }
constexpr Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w }; }
constexpr Quaternion operator-(const Quaternion& lhs, const Quaternion& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w }; }
constexpr Quaternion operator*(const float& lhs, const Quaternion& rhs) { return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w }; }
constexpr bool operator==(const Quaternion& lhs, const Quaternion& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
constexpr bool operator!=(const Quaternion& lhs, const Quaternion& rhs) { return !(lhs == rhs); }
constexpr Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
	return {
		lhs.m0 * rhs.m0 + lhs.m1 * rhs.m4 + lhs.m2 * rhs.m8 + lhs.m3 * rhs.m12,
		lhs.m4 * rhs.m0 + lhs.m5 * rhs.m4 + lhs.m6 * rhs.m8 + lhs.m7 * rhs.m12,
		lhs.m8 * rhs.m0 + lhs.m9 * rhs.m4 + lhs.m10 * rhs.m8 + lhs.m11 * rhs.m12,
		lhs.m12 * rhs.m0 + lhs.m13 * rhs.m4 + lhs.m14 * rhs.m8 + lhs.m15 * rhs.m12,
		lhs.m0 * rhs.m1 + lhs.m1 * rhs.m5 + lhs.m2 * rhs.m9 + lhs.m3 * rhs.m13,
		lhs.m4 * rhs.m1 + lhs.m5 * rhs.m5 + lhs.m6 * rhs.m9 + lhs.m7 * rhs.m13,
		lhs.m8 * rhs.m1 + lhs.m9 * rhs.m5 + lhs.m10 * rhs.m9 + lhs.m11 * rhs.m13,
		lhs.m12 * rhs.m1 + lhs.m13 * rhs.m5 + lhs.m14 * rhs.m9 + lhs.m15 * rhs.m13,
		lhs.m0 * rhs.m2 + lhs.m1 * rhs.m6 + lhs.m2 * rhs.m10 + lhs.m3 * rhs.m14,
		lhs.m4 * rhs.m2 + lhs.m5 * rhs.m6 + lhs.m6 * rhs.m10 + lhs.m7 * rhs.m14,
		lhs.m8 * rhs.m2 + lhs.m9 * rhs.m6 + lhs.m10 * rhs.m10 + lhs.m11 * rhs.m14,
		lhs.m12 * rhs.m2 + lhs.m13 * rhs.m6 + lhs.m14 * rhs.m10 + lhs.m15 * rhs.m14,
		lhs.m0 * rhs.m3 + lhs.m1 * rhs.m7 + lhs.m2 * rhs.m11 + lhs.m3 * rhs.m15,
		lhs.m4 * rhs.m3 + lhs.m5 * rhs.m7 + lhs.m6 * rhs.m11 + lhs.m7 * rhs.m15,
		lhs.m8 * rhs.m3 + lhs.m9 * rhs.m7 + lhs.m10 * rhs.m11 + lhs.m11 * rhs.m15,
		lhs.m12 * rhs.m3 + lhs.m13 * rhs.m7 + lhs.m14 * rhs.m11 + lhs.m15 * rhs.m15,
	};
}
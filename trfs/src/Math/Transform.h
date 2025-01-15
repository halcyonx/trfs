#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

// math aliases for glm types
namespace Math
{
	struct Transform
	{
		static Mat4 Translate(const Mat4& matrix, const Vec3& translation)
		{
			return glm::translate(matrix, translation);
		}

		static Mat4 Rotate(const Mat4& matrix, float angleDegrees, const Vec3& axis)
		{
			return glm::rotate(matrix, angleDegrees, axis);
		}

		static Mat4 Scale(const Mat4& matrix, const Vec3& scalingFactors)
		{
			return glm::scale(matrix, scalingFactors);
		}

		static Mat4 Identity()
		{
			return Mat4(1.0f);
		}
	};

	inline float Radians(float degrees)
	{
		return glm::radians(degrees);
	}

	inline Mat4 Perspective(float fovDegrees, float aspectRatio, float near, float far)
	{
		return glm::perspective(fovDegrees, aspectRatio, near, far);
	}
} // namespace Math

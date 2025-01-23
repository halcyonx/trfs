#include "Camera.h"
#include <Core/Input.h>
#include <glm/ext/matrix_transform.hpp>
#include <Core/Log.h>

namespace Render
{
	Camera::Camera()
	{
		UpdateLastPos();
	}

	Camera::Camera(const Vec3& pos, const Vec3& wup)
		: _position(pos)
		, _wup(wup)
	{
		Calculate();
	}

	void Camera::SetPosition(const Vec3& pos)
	{
		_position = pos;
		Calculate();
	}

	Vec3 Camera::GetPosition() const
	{
		return _position;
	}

	Vec3 Camera::GetDirection() const
	{
		return _front;
	}

	void Camera::SetUp(const Vec3& up)
	{
		_up = up;
		Calculate();
	}

	void Camera::SetPitch(float pitch)
	{
		_pitch = pitch;
		Calculate();
	}

	void Camera::SetYaw(float yaw)
	{
		_yaw = yaw;
		Calculate();
	}

	void Camera::SetFov(float fov)
	{
		_fov = fov;
		Calculate();
	}

	Mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(_position, _position + _front, _up);
	}

	void Camera::OnUpdate(float dt)
	{
		// process input
		float cameraSpeed = _movementSpeed * dt;
		if (Input::IsKeyPressed(Keycode::KEY_W)) {
			_position += cameraSpeed * _front;
		}

		if (Input::IsKeyPressed(Keycode::KEY_S)) {
			_position -= cameraSpeed * _front;
		}

		if (Input::IsKeyPressed(Keycode::KEY_A)) {
			_position -= glm::normalize(glm::cross(_front, _up)) * cameraSpeed;
		}

		if (Input::IsKeyPressed(Keycode::KEY_D)) {
			_position += glm::normalize(glm::cross(_front, _up)) * cameraSpeed;
		}
	}

	void Camera::OnMouseMovedEvent(int x, int y)
	{
		const auto xoffset = static_cast<float>(x) * _sensitivity;
		const auto yoffset = -1 * static_cast<float>(y) * _sensitivity;

		_lastMouseX += xoffset;
		_lastMouseY += yoffset;

		_yaw += xoffset;
		_pitch += yoffset;
		_pitch = std::clamp(_pitch, -89.0f, 89.0f);
		Calculate();
	}

	void Camera::OnMouseScrolledEvent(int offset)
	{
		if (_fov >= 1.0f && _fov <= 45.0f) {
			_fov -= static_cast<float>(offset);
		}

		_fov = std::clamp(_fov, 1.0f, 45.0f);
		Calculate();
	}

	void Camera::Calculate()
	{
		Vec3 front;
		front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		front.y = sin(glm::radians(_pitch));
		front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_front = glm::normalize(front);
		_right = glm::normalize(glm::cross(_front, _wup));
		_up = glm::normalize(glm::cross(_right, _front));
	}

	void Camera::UpdateLastPos()
	{
		//		double mouseX, mouseY;
		//		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		//		glfwGetCursorPos(window, &mouseX, &mouseY);
		//		_lastMouseX = static_cast<float>(mouseX);
		//		_lastMouseY = static_cast<float>(mouseY);
	}

	void Camera::SetMoveSpeed(float speed)
	{
		_movementSpeed = speed;
	}

	float Camera::GetMoveSpeed() const
	{
		return _movementSpeed;
	}
} // namespace Render

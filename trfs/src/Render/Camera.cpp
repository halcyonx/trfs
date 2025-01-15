#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

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

	//	void Camera::OnEvent(Core::Event& event)
	//	{
	//		EventDispatcher dispatcher(event);
	//		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Camera::OnMouseMoved, this, std::placeholders::_1));
	//		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&Camera::OnMouseScrolled, this, std::placeholders::_1));
	//	}

	void Camera::OnUpdate(float ts)
	{
		//		ProcessInput(ts);
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

	//	bool Camera::OnMouseMoved(const MouseMovedEvent& event)
	//	{
	//		const float xpos = event.GetX();
	//		const float ypos = event.GetY();
	//		float xoffset = (xpos - _lastMouseX) * _sensitivity;
	//		float yoffset = (_lastMouseY - ypos) * _sensitivity;
	//		_lastMouseX = xpos;
	//		_lastMouseY = ypos;
	//
	//		_yaw += xoffset;
	//		_pitch += yoffset;
	//		_pitch = std::clamp(_pitch, -89.0f, 89.0f);
	//		Calculate();
	//		return false;
	//	}

	//	bool Camera::OnMouseScrolled(const MouseScrolledEvent& event)
	//	{
	//		if (_fov >= 1.0f && _fov <= 45.0f) {
	//			_fov -= event.GetYOffset();
	//		}
	//
	//		_fov = std::clamp(_fov, 1.0f, 45.0f);
	//		Calculate();
	//		return false;
	//	}

	//	void Camera::ProcessInput(float dt)
	//	{
	//		float cameraSpeed = _movementSpeed * dt;
	//		if (Input::IsKeyPressed(KEY_W)) {
	//			_position += cameraSpeed * _front;
	//		}
	//
	//		if (Input::IsKeyPressed(KEY_S)) {
	//			_position -= cameraSpeed * _front;
	//		}
	//
	//		if (Input::IsKeyPressed(KEY_A)) {
	//			_position -= glm::normalize(glm::cross(_front, _up)) * cameraSpeed;
	//		}
	//
	//		if (Input::IsKeyPressed(KEY_D)) {
	//			_position += glm::normalize(glm::cross(_front, _up)) * cameraSpeed;
	//		}
	//	}

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

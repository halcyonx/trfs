#pragma once

namespace Render
{
	class Camera
	{
	public:
		Camera();
		Camera(const Vec3& pos, const Vec3& wup);

		Vec3 GetPosition() const;
		Vec3 GetDirection() const;
		Mat4 GetViewMatrix() const;

		float GetMoveSpeed() const;
		float GetYaw() const { return _yaw; }
		float GetPitch() const { return _pitch; }
		float GetFov() const { return _fov; }

		void SetPosition(const Vec3& pos);
		void SetUp(const Vec3& up);
		void SetPitch(float pitch);
		void SetYaw(float yaw);
		void SetFov(float fov);
		void SetMoveSpeed(float speed);

		void OnUpdate(float ts);
		void UpdateLastPos();

	private:
		void Calculate();

	private:
		Vec3 _position = Vec3 { 0.0f, 0.0f, 0.0f };
		Vec3 _front = Vec3 { 0.0f, 0.0f, -1.0f };
		Vec3 _right = Vec3 { 0.0f, 0.0f, 0.0f };
		Vec3 _up = Vec3 { 0.0f, 1.0f, 0.0f };
		Vec3 _wup = Vec3 { 0.0f, 1.0f, 0.0f };
		float _pitch = 0.0f;
		float _yaw = -90.0f;
		float _movementSpeed = 2.5f;
		float _sensitivity = 0.1f;
		float _fov = 45.0f;
		float _lastMouseX = 0.0f;
		float _lastMouseY = 0.0f;
	};
} // namespace Render

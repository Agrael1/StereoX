#pragma once
#include <QAbstractCameraController>

namespace ver
{
	class StereoCamera;
	class CameraController : public Qt3DExtras::QAbstractCameraController
	{
	public:
		CameraController(StereoCamera& cam)noexcept
			:cam(cam){}
	public:
		virtual void moveCamera(const InputState& state, float dt) override;
	private:
		StereoCamera& cam;
	};
}
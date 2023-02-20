#include <CameraController.h>
#include <Camera.h>

void ver::CameraController::moveCamera(const InputState& state, float dt)
{
	cam.Translate(QVector3D(
		state.txAxisValue * linearSpeed(),
		state.tyAxisValue * linearSpeed(),
		state.tzAxisValue * linearSpeed()
	) * dt);


}

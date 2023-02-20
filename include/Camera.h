#pragma once
#include <QCameraLens>
#include <QCamera>
#include <DirectXMath.h>

#if defined(near) || defined(far)
#undef near 
#undef far 
#endif // defined(near) || defined(far)


namespace ver
{
	inline [[nodiscard("Calculation of the shear matrix")]]
		QMatrix4x4 ShearZ(float x, float y)noexcept
	{
		QMatrix4x4 m;
		m.setRow(0, { 1,0,x,0 });
		m.setRow(1, { 0,1,y,0 });
		return m.transposed();
	}

	class Camera : public Qt3DCore::QEntity
	{
		static inline constexpr QVector3D up{ 0.0f,1.0f,0.0f };
		static inline constexpr QVector4D forward_base{ 0.0f,0.0f,1.0f,0.0f };
	public:
		Camera(float fov = 90.0f, float aspect_ratio = 16.0f / 9.0f, float pnear = 0.5f, float pfar = 1000.0f)noexcept
		{
			SetProjection(fov, aspect_ratio, pnear, pfar);
			UpdateView();
			Finalize();
		}
	public:
		void SetRotation(QVector3D xrotation)noexcept
		{
			rotation = xrotation; UpdateView();
		}
		void SetPosition(QVector3D xposition)noexcept
		{
			position = xposition; UpdateView();
		}
		void SetXDisplacement(float xdisp)noexcept
		{
			x_displacement = xdisp; UpdateView();
		}
		void SetProjection(float fov, float aspect_ratio, float near = 0.5f, float far = 1000.0f)noexcept
		{
			QMatrix4x4 m;
			m.perspective(fov, aspect_ratio, near, far);
			perspective.setProjectionMatrix(m);
		}
		void UpdateView()noexcept
		{
			view_matrix.setMatrix(GetViewMatrix());
		}
		auto GetPosition()const noexcept
		{
			return position;
		}
		auto GetRotation()const noexcept
		{
			return rotation;
		}
	private:
		[[nodiscard("Calculation of the view matrix")]]
		QMatrix4x4 GetViewMatrix()const noexcept
		{
			QMatrix4x4 m;
			m.rotate(QQuaternion::fromEulerAngles(rotation));
			auto direction = (forward_base * m).toVector3D();

			direction.normalize();
			auto right = QVector3D::crossProduct(up, direction).normalized();
			auto up_recalc = QVector3D::crossProduct(direction, right);

			auto neg_eye = -right * x_displacement - position;
			auto d0 = QVector3D::dotProduct(right, neg_eye);
			auto d1 = QVector3D::dotProduct(up_recalc, neg_eye);
			auto d2 = QVector3D::dotProduct(direction, neg_eye);

			m.setRow(0, QVector4D{ right,d0 });
			m.setRow(1, QVector4D{ up_recalc,d1 });
			m.setRow(2, QVector4D{ direction,d2 });
			m.setRow(3, QVector4D{ 0,0,0,1 });

			return m.transposed() * ShearZ(ShearCoefficient(), 0);
		}
		[[nodiscard]] float ShearCoefficient()const noexcept
		{
			return x_displacement / focus_distance;
		}
		void Finalize()noexcept
		{
			addComponent(&perspective);
			addComponent(&view_matrix);
		}
	private:
		QVector3D position;
		float x_displacement = 0.0f;
		QVector3D rotation;
		float focus_distance = 1.0f;

		Qt3DRender::QCameraLens perspective;
		Qt3DCore::QTransform view_matrix;

		Qt3DRender::QCamera cam;
	};

	class StereoCamera
	{
	public:
		StereoCamera(float fov = 90.0f, float aspect_ratio = 16.f / 9.f)noexcept
			:left(fov, aspect_ratio),
			right(fov, aspect_ratio)
		{}
	public:
		template<class Self>
		auto& GetLeftCamera(this Self&& self)noexcept
		{
			return self.left;
		}
		template<class Self>
		auto& GetRightCamera(this Self&& self)noexcept
		{
			return self.right;
		}
	public:
		void SetEyeDistance(float dist)noexcept
		{
			left.SetXDisplacement(-eye_dist * 0.5f);
			right.SetXDisplacement(eye_dist * 0.5f);
		}
		void SetPosition(QVector3D pos)noexcept
		{
			left.SetPosition(pos);
			right.SetPosition(pos);
		}
		void SetProjection(float fov = 90.0f, float aspect_ratio = 16.f / 9.f)noexcept
		{
			left.SetProjection(fov, aspect_ratio);
			right.SetProjection(fov, aspect_ratio);
		}
		void Translate(QVector3D delta)noexcept
		{
			auto xpos = QVector4D(left.GetPosition());
			QMatrix4x4 m;
			m.rotate(QQuaternion::fromEulerAngles(left.GetRotation()));
			SetPosition((xpos * m).toVector3D());
		}
	private:
		Camera left;
		Camera right;
		float eye_dist = 0.0f;
	};
}
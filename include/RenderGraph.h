#pragma once
#include <QRenderTarget>
#include <QCameraSelector>
#include <QClearBuffers>
#include <QForwardRenderer>
#include <QRenderSurfaceSelector>
#include <QRenderTargetSelector>
#include <QViewport>

namespace ver::rg
{
	class RenderGraph : public Qt3DRender::QFrameGraphNode
	{
	public:
		RenderGraph(QObject* render_surface)
		{
			surface.setSurface(render_surface);

			viewport.setNormalizedRect({ 0.0,0.0,1.0,1.0 });

			clear.setClearColor(Qt::cyan);
			clear.setBuffers(Qt3DRender::QClearBuffers::ColorDepthBuffer);
			clear_depth.setBuffers(Qt3DRender::QClearBuffers::DepthBuffer);

			Finalize();
		}
	public:
		void SetCameras(Qt3DCore::QEntity* cam_left, Qt3DCore::QEntity* cam_right)
		{
			left_camera.setCamera(cam_left);
			right_camera.setCamera(cam_right);
		}
	private:
		void Finalize()noexcept
		{
			surface.setParent(this);
			viewport.setParent(&surface);

			clear.setParent(&viewport);
			left_camera.setParent(&clear);

			clear_depth.setParent(&left_camera);
			right_camera.setParent(&clear_depth);
		}

	private:
		Qt3DRender::QRenderSurfaceSelector surface;
		Qt3DRender::QViewport viewport;
		Qt3DRender::QClearBuffers clear;

		Qt3DRender::QCameraSelector left_camera;
		Qt3DRender::QRenderTargetSelector left_target;

		Qt3DRender::QClearBuffers clear_depth;
		Qt3DRender::QCameraSelector right_camera;
		Qt3DRender::QRenderTargetSelector right_target;
	};
}
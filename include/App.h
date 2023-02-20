#pragma once
#include <QApplication>
#include <Scene.h>
#include <Camera.h>
#include <RenderGraph.h>
#include <MainWindow.h>



namespace ver
{
	class App
	{
		static inline constexpr float fov = 60.0f;
	public:
		App(int& argc, char** argv);
	public:
		int Start(){return app.exec();}
	private:
		static void SetDefaultSurface()noexcept;
		void SetStyle()noexcept;
	private:
		QApplication app;
		MainWindow window;

		Scene root;
		rg::RenderGraph rg;
		StereoCamera cam;
	};
}
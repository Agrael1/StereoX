#include <QStyleFactory>
#include <App.h>


ver::App::App(int& argc, char** argv)
	:app(argc, argv)
	, root(window.View())
	, rg(&window.View())
	, cam(fov, window.View().width() / window.View().height())
{
	SetDefaultSurface();
	SetStyle();
	rg.SetCameras(&cam.GetLeftCamera(), &cam.GetRightCamera());

	auto aspect_changed = [this](int width) {cam.SetProjection(fov, float(window.View().width()) / float(window.View().height())); };

	QObject::connect(&window.View(), &QWindow::widthChanged, aspect_changed);
	QObject::connect(&window.View(), &QWindow::heightChanged, aspect_changed);

	window.View().setActiveFrameGraph(&rg);
	window.show();
}

void ver::App::SetDefaultSurface() noexcept
{
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setSamples(0);
	format.setStereo(true);
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setMajorVersion(4);
	format.setMinorVersion(5);
	QSurfaceFormat::setDefaultFormat(format);
}

void ver::App::SetStyle() noexcept
{
	QApplication::setApplicationName(u"Veritas Engine"_qs);
	QApplication::setApplicationVersion(u"0.1.0"_qs);
	app.setStyle(QStyleFactory::create(u"fusion"_qs));

	// Style definition (darkmode)
	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
	darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);
	app.setPalette(darkPalette);
}

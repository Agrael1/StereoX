#include <MainWindow.h>
#include <DockAreaWidget.h>

ver::MainWindow::MainWindow()
{
	setCentralWidget(&docker);
	auto container = createWindowContainer(&view, this);
	ads::CDockWidget& view3d = *new ads::CDockWidget(u"View"_qs);
	view3d.setWidget(container);
	auto* area = docker.setCentralWidget(&view3d);
	resize({ 1920,1080 });
	area->setAllowedAreas(ads::DockWidgetArea::OuterDockAreas);
}

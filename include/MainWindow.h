#pragma once
#include <Qt3DWindow>
#include <QMainWindow>
#include <DockManager.h>


namespace ver
{

	class A : public Qt3DExtras::Qt3DWindow
	{
	public:
		using base = Qt3DExtras::Qt3DWindow;

		//TBD
		bool event(QEvent* event) override
		{
			switch (event->type()) {
			case QEvent::Type::Leave:
				//BlockMouse();
				//event->accept();
				break;
			}
			return base::event(event);
		}
	private:
		void BlockMouse()noexcept
		{
			const QRect& rect = geometry();
			QPoint position = mapFromGlobal(QCursor::pos());

			// Check the bounds
			qint32 x = qBound(rect.left(), position.x(), rect.right());
			qint32 y = qBound(rect.top(), position.y(), rect.bottom());

			// Adjust the cursor
			if (x != position.x() || y != position.y())
				QCursor::setPos(mapToGlobal(geometry().center()));
		}
	};


	class MainWindow : public QMainWindow
	{
		using base = QMainWindow;
	public:
		MainWindow();
	public:
		template<class Self>
		auto& View(this Self&& self)noexcept
		{
			return self.view;
		}

	private:
		ads::CDockManager docker;
		A view;
	};
}
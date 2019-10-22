#include "uimainwindow.h"

#include <QMainWindow>
#include <QWidget>

void UIMainWindow::setupUI(QMainWindow* main_window)
{
	/* For the current moment we are not using main window,
	 * but we will leave it to handle tray icon events */
	main_window->resize({ 0,0 });
	main_window->hide();

	central_widget_ = new QWidget{ main_window };
	main_window->setCentralWidget(central_widget_);
}
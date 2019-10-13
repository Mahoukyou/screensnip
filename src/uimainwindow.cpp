#include "uimainwindow.h"

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

void UIMainWindow::setupUI(QMainWindow* main_window)
{
	const auto desktop_size = QApplication::desktop()->screenGeometry(); // todo, use screens();
	main_window->resize(desktop_size.size() * 0.7);
	main_window->showMaximized();

	central_widget_ = new QWidget{ main_window };
	main_window->setCentralWidget(central_widget_);

	snip_button_ = new QPushButton{ centralWidget() };
	snip_button_->setText("settings");
}
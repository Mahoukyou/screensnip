#include "uisettingswindow.h"

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

void UISettingsWindow::setupUI(QMainWindow* const settings_window)
{
	const auto desktop_size = QApplication::desktop()->screenGeometry(); // todo, use screens();
	settings_window->resize(desktop_size.size() * 0.5);

	central_widget_ = new QWidget{ settings_window };
	settings_window->setCentralWidget(central_widget_);

	QVBoxLayout* const vertical_layout = new QVBoxLayout{ centralWidget() };
	QGridLayout* const form_layout = new QGridLayout{ centralWidget() };
	vertical_layout->addLayout(form_layout);
	form_layout->addWidget(new QLabel{ "Save path:" }, 0, 0);
	save_path_edit_ = new QLineEdit{ centralWidget() };
	form_layout->addWidget(save_path_edit_, 0, 1);
	save_path_button_ = new QPushButton{ "Browse...", centralWidget() };
	form_layout->addWidget(save_path_button_, 0, 2);


	//form_layout->addWidget(new QWidget{ centralWidget() }, 1, 0, 0, 2);
	QHBoxLayout* const horizontal_layout = new QHBoxLayout{ centralWidget() };
	vertical_layout->addStretch(1);
	vertical_layout->addLayout(horizontal_layout);
	save_changes_button_ = new QPushButton{ "Save", centralWidget() };
	horizontal_layout->addWidget(save_changes_button_);
	cancel_changes_button_ = new QPushButton{ "Cancel", centralWidget() };
	horizontal_layout->addWidget(cancel_changes_button_);
}

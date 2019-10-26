#include "uisettingswindow.h"

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

void UISettingsWindow::setupUI(QWidget* const settings_widget)
{
	const auto desktop_size = QApplication::desktop()->screenGeometry(); // todo, use screens();
	settings_widget->resize(desktop_size.size() * 0.5);

	QVBoxLayout* const vertical_layout = new QVBoxLayout{ settings_widget };
	QGridLayout* const form_layout = new QGridLayout{ settings_widget };
	vertical_layout->addLayout(form_layout);

	form_layout->addWidget(new QLabel{ "Save to file: "}, 0, 0);
	save_to_file_checkbox_ = new QCheckBox{ settings_widget };
	form_layout->addWidget(save_to_file_checkbox_, 0, 1);

	form_layout->addWidget(new QLabel{ "Save path:" }, 1, 0);
	save_path_edit_ = new QLineEdit{ settings_widget };
	form_layout->addWidget(save_path_edit_, 1, 1);
	save_path_button_ = new QPushButton{ "Browse...", settings_widget };
	form_layout->addWidget(save_path_button_, 1, 2);

	//form_layout->addWidget(new QWidget{ centralWidget() }, 1, 0, 0, 2);
	QHBoxLayout* const horizontal_layout = new QHBoxLayout{ settings_widget };
	vertical_layout->addStretch(1);
	vertical_layout->addLayout(horizontal_layout);
	save_changes_button_ = new QPushButton{ "Save", settings_widget };
	horizontal_layout->addWidget(save_changes_button_);
	cancel_changes_button_ = new QPushButton{ "Cancel", settings_widget };
	horizontal_layout->addWidget(cancel_changes_button_);
}

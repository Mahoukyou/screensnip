#include "settingswindow.h"

#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

#include "settings.h"
#include "utility.h"

SettingsWindow::SettingsWindow(QWidget* const parent) :
	QWidget{ parent },
	ui_{ std::make_unique<UISettingsWindow>() }
{
	ui_->setupUI(this);

	setupInitialSettings();

	connect(ui_->saveChangesButton(), &QPushButton::clicked, this, &SettingsWindow::saveChanges);
	connect(ui_->cancelChangesButton(), &QPushButton::clicked, this, &SettingsWindow::cancelChanges);
}

void SettingsWindow::setupInitialSettings()
{
	const Settings& settings = Settings::instance();
	
	ui_->savePathEdit()->setText(settings.saveDirectoryPath());
}

bool SettingsWindow::validatePendingChanges()
{
	bool changes_valid{ true };

	const QString new_directory_path = ui_->savePathEdit()->text();
	if (!utility::makeDirectoryPathIfNotExists(new_directory_path))
	{
		changes_valid = false;
		qDebug() << "Invalid directory path or not enough permissions to make one";
	}

	return changes_valid;
}

void SettingsWindow::saveChanges()
{
	Settings& settings = Settings::instance();
	// todo, block input

	if(!validatePendingChanges())
	{
		// todo
		qDebug() << "settings are invalid";
		return;
	}
	
	settings.setSaveDirectoryPath(ui_->savePathEdit()->text());

	
	hide();
	deleteLater();
}

void SettingsWindow::cancelChanges()
{
	hide();
	deleteLater();
}

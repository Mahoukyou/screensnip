#pragma once

#include <QMainWindow>
#include "uisettingswindow.h"

class SettingsWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit SettingsWindow(QWidget* parent = nullptr);
	~SettingsWindow() = default;

private:
	std::unique_ptr<UISettingsWindow> ui_;

	void setupInitialSettings();

	[[nodiscard]] bool validatePendingChanges();
	
	void saveChanges();
	void cancelChanges();
};
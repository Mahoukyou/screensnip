#pragma once

#include <QWidget>
#include "uisettingswindow.h"

class SettingsWindow : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsWindow(QWidget* parent = nullptr);
	~SettingsWindow() = default;

private:
	std::unique_ptr<UISettingsWindow> ui_;

	void setupInitialSettings();

	void enableInput(bool enable);
	[[nodiscard]] bool validatePendingChanges();

	void saveChanges();
	void cancelChanges();
};
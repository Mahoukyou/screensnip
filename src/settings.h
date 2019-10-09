#pragma once

#include <QSettings>

class Settings
{
public:
	Settings(const Settings&) = delete;
	Settings(Settings&&) = delete;

	Settings& operator=(const Settings&) = delete;
	Settings& operator=(Settings&&) = delete;

private:
	Settings();

public:
	static Settings& instance();
	
	void setSnipWidgetHotkey(const QString& hotkey);
	QString getSnipWidgetHotkey() const;

	void setEntireScreenshotHotkey(const QString& hotkey);
	QString getEntireScreenshotHotkey() const;

private:
	static QString snipWidgetHotkeySettingsKey();
	static QString entireScreenshotHotkeySettingsKey();
	
private:
	QSettings settings_;
};
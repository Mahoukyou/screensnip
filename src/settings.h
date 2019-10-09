#pragma once

#include <QSettings>
#include <QObject>

class Settings : public QObject
{
	Q_OBJECT
	
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
	[[nodiscard]] QString getSnipWidgetHotkey() const;

	void setEntireScreenshotHotkey(const QString& hotkey);
	[[nodiscard]] QString getEntireScreenshotHotkey() const;

signals:
	void onSnipWidgetHotkeyChanged(const QString& hotkey);
	void onEntireScreenshotHotkeyChanged(const QString& hotkey);

private:
	static QString snipWidgetHotkeySettingsKey();
	static QString entireScreenshotHotkeySettingsKey();
	
private:
	QSettings settings_;
};
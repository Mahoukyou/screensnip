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
	[[nodiscard]] QString snipWidgetHotkey() const;

	void setEntireScreenshotHotkey(const QString& hotkey);
	[[nodiscard]] QString entireScreenshotHotkey() const;

	void setMultipleSnipsModifier(Qt::KeyboardModifier key);
	[[nodiscard]] Qt::KeyboardModifier multipleSnipsModifier() const;

signals:
	void onSnipWidgetHotkeyChanged(const QString& hotkey);
	void onEntireScreenshotHotkeyChanged(const QString& hotkey);

private:
	static QString snipWidgetHotkeySettingsKey();
	static QString entireScreenshotHotkeySettingsKey();
	static QString multipleSnipsSettingsKey();
	
private:
	QSettings settings_;
};
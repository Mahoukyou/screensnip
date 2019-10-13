#pragma once

#include <QSettings>
#include <QObject>

class Settings : public QObject
{
	Q_OBJECT
	
public:
	~Settings() = default;
	
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

	void setSaveDirectoryPath(const QString& path);
	[[nodiscard]] QString saveDirectoryPath() const;

signals:
	void onSnipWidgetHotkeyChanged(const QString& hotkey);
	void onEntireScreenshotHotkeyChanged(const QString& hotkey);

private:
	[[nodiscard]] static QString snipWidgetHotkeySettingsKey();
	[[nodiscard]] static QString entireScreenshotHotkeySettingsKey();
	[[nodiscard]] static QString multipleSnipsSettingsKey();
	[[nodiscard]] static QString saveDirectoryPathSettingsKey();
	
private:
	QSettings settings_;
};
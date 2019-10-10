#include "settings.h"

Settings::Settings() :
	settings_{"SoIAS", "ScreenSnip"}
{
	
}

Settings& Settings::instance()
{
	static Settings settings{};

	return settings;
}

void Settings::setSnipWidgetHotkey(const QString& hotkey)
{
	settings_.setValue(snipWidgetHotkeySettingsKey(), hotkey);
	emit onSnipWidgetHotkeyChanged(hotkey);
}

QString Settings::snipWidgetHotkey() const
{
	return settings_.value(snipWidgetHotkeySettingsKey(), "Alt+Shift+S").toString();
}

void Settings::setEntireScreenshotHotkey(const QString& hotkey)
{
	settings_.setValue(entireScreenshotHotkeySettingsKey(), hotkey);
	emit onEntireScreenshotHotkeyChanged(hotkey);
}

QString Settings::entireScreenshotHotkey() const
{
	return settings_.value(entireScreenshotHotkeySettingsKey(), "Alt+Shift+D").toString();
}

void Settings::setMultipleSnipsModifier(const Qt::KeyboardModifier key)
{
	settings_.setValue(multipleSnipsSettingsKey(), key);
}

Qt::KeyboardModifier Settings::multipleSnipsModifier() const
{
	const int value = settings_.value(multipleSnipsSettingsKey(), Qt::KeyboardModifier::ShiftModifier).toInt();
	return static_cast<Qt::KeyboardModifier>(value);
}

void Settings::setSaveDirectoryPath(const QString& path)
{
	settings_.setValue(saveDirectoryPathSettingsKey(), path);
}

QString Settings::saveDirectoryPath() const
{
	// todo, default path
	return settings_.value(saveDirectoryPathSettingsKey(), "").toString();
}

QString Settings::snipWidgetHotkeySettingsKey()
{
	return "snip_widget_hotkey";
}

QString Settings::entireScreenshotHotkeySettingsKey()
{
	return "entire_screenshot_hotkey";
}

QString Settings::multipleSnipsSettingsKey()
{
	return "multiple_snips_key";
}

QString Settings::saveDirectoryPathSettingsKey()
{
	return "save_directory_path";
}

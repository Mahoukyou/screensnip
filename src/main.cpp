//#include "vld.h"

#include <QApplication>
#include "mainwindow.h"

#include "hotkeymanager.h"
#include "settings.h"

int main(int argc, char *argv[])
{
	int result{};
	{
		QApplication a(argc, argv);
		QGuiApplication::setQuitOnLastWindowClosed(false);

		Settings& settings = Settings::instance();
		settings.setSaveDirectoryPath(R"(K:\Snips\)");
		
		HotkeyManager hotkey_manager;
		hotkey_manager.setupHotkey(settings.snipWidgetHotkey(), HotkeyManager::EHotkey::SnipWidget);
		hotkey_manager.setupHotkey(settings.entireScreenshotHotkey(), HotkeyManager::EHotkey::EntireScreenshot);

		QObject::connect(&settings, &Settings::onSnipWidgetHotkeyChanged, &hotkey_manager, [&hotkey_manager](const QString& hotkey)
		{
			hotkey_manager.setupHotkey(hotkey, HotkeyManager::EHotkey::SnipWidget);
		});

		QObject::connect(&settings, &Settings::onEntireScreenshotHotkeyChanged, &hotkey_manager, [&hotkey_manager](const QString& hotkey)
		{
			hotkey_manager.setupHotkey(hotkey, HotkeyManager::EHotkey::EntireScreenshot);
		});

		MainWindow window;
		//window.show();

		result = a.exec();
	}

	return result;
}

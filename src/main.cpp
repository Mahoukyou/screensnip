#include "vld.h"

#include <QApplication>
#include "mainwindow.h"

#include "hotkeymanager.h"
#include "settings.h"


int main(int argc, char *argv[])
{
	int result{};
	{
		QApplication a(argc, argv);

		Settings& settings = Settings::instance();
		settings.setSnipWidgetHotkey("Alt+Shift+S");
		settings.setEntireScreenshotHotkey("Alt+Shift+D");

		HotkeyManager& hotkey_manager = HotkeyManager::instance();
		hotkey_manager.setupHotkey(settings.getSnipWidgetHotkey(), HotkeyManager::EHotkey::SnipWidget);
		hotkey_manager.setupHotkey(settings.getEntireScreenshotHotkey(), HotkeyManager::EHotkey::EntireScreenshot);
		
		MainWindow window;
		window.show();

		result = a.exec();
	}

	return result;
}

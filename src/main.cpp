#include "vld.h"

#include <QApplication>
#include "mainwindow.h"

#include "uglobalhotkeys.h"
#include <QDebug>

#include "snipwidget.h"
#include "utility.h"


int main(int argc, char *argv[])
{
	int result{};
	{
		QApplication a(argc, argv);

		// teest
		UGlobalHotkeys* hotkeyManager = new UGlobalHotkeys();
		hotkeyManager->registerHotkey("Alt+Shift+S", 1);
		hotkeyManager->registerHotkey("Alt+Shift+D", 2);
		QObject::connect(hotkeyManager, &UGlobalHotkeys::activated, [](const size_t id)
		{
			// todo, enumerator, hotkey manager
			switch(id)
			{
			case 1:
			{
				auto snip_widget = SnipWidget::create_snip_widget();
				snip_widget->show();
				snip_widget->raise();
				snip_widget->activateWindow();

				break;
			}
			case 2:
				utility::takeEntireScreenScreenshot();
				break;

			default:;
			}
			
			
		});
		
		MainWindow window;
		window.show();

		result = a.exec();
	}

	return result;
}
